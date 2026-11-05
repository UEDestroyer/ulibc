#!/usr/bin/env python3
import os
import re
import sys
from pathlib import Path

UE_INCLUDE_DIR = Path("/mnt/H/include/low-access-UEDestroyer/")
TARGET_EXTENSIONS = {".c", ".h", ".S", ".s", ".cpp", ".hpp"}
IGNORE_DIRS = {".git", "build", "dist", ".cache", "low-access-UEDestroyer"}

# Ключевые слова, которые могут стоять прямо перед вызовом функции в выражении
EXPRESSION_KEYWORDS = {"return", "sizeof", "case"}

def get_ue_functions(include_dir: Path) -> set[str]:
    """Сканирует include и собирает базовые имена (без ue_)."""
    if not include_dir.exists():
        print(f"[-] Ошибка: директория не найдена: {include_dir}", file=sys.stderr)
        sys.exit(1)

    ue_pattern = re.compile(r"\bue_([a-zA-Z0-9_]+)\b")
    functions = set()

    for root, _, files in os.walk(include_dir):
        for file in files:
            path = Path(root) / file
            try:
                content = path.read_text(encoding="utf-8", errors="ignore")
                for match in ue_pattern.finditer(content):
                    functions.add(match.group(1))
            except Exception as e:
                print(f"[!] Не удалось прочитать {path}: {e}", file=sys.stderr)

    return functions

def is_declaration_or_definition(prefix: str, prev_line: str) -> bool:
    """Определяет, является ли совпадение объявлением/сигнатурой или вызовом функции."""
    prefix = prefix.strip()

    # 1. Если перед функцией пусто, проверяем предыдущую строку (на случай многострочного объявления: pid_t \n getpid())
    if not prefix:
        prev = prev_line.strip()
        # Если предыдущая строка похожа на тип возвращаемого значения (pid_t, int*, static inline void)
        if prev and not prev.endswith((";", "{", "}", ",", ")", ":")):
            return True
        return False

    # 2. Вызов через указатель на структуру/метод: obj.read(...) или vfs->read(...)
    if prefix.endswith((".", "->")):
        return True

    # 3. Убираем указатели перед именем (например, "char *" -> "char")
    clean_prefix = re.sub(r"\*+\s*$", "", prefix).rstrip()

    # 4. Проверяем последнее слово перед именем функции
    last_word_match = re.search(r"([a-zA-Z_][a-zA-Z0-9_]*)$", clean_prefix)
    if last_word_match:
        last_word = last_word_match.group(1)
        # Если перед функцией стоит 'return' или 'sizeof' — это 100% вызов
        if last_word in EXPRESSION_KEYWORDS:
            return False
        # Если стоит любое другое слово без оператора (например, "pid_t getpid", "extern int read") —
        # это тип, спецификатор или макрос объявления -> пропускаем!
        return True

    return False

def strip_comments_and_strings(line: str) -> str:
    """Удаляет строковые литералы и однострочные комментарии."""
    line = re.sub(r'"([^"\\]|\\.)*"', '""', line) # строки "..."
    line = re.sub(r"//.*$", "", line)             # комментарии //
    return line

def search_usages(functions: set[str]):
    if not functions:
        print("[-] Функции ue_* не найдены.")
        return

    print(f"[+] Загружено {len(functions)} функций для поиска вызовов.")

    pattern_str = r"\b(" + "|".join(re.escape(f) for f in sorted(functions, key=len, reverse=True)) + r")\s*\("
    call_pattern = re.compile(pattern_str)

    cwd = Path.cwd()
    matches_count = 0

    for root, dirs, files in os.walk(cwd):
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]

        for file in files:
            path = Path(root) / file
            if path.suffix not in TARGET_EXTENSIONS:
                continue

            if UE_INCLUDE_DIR.resolve() in path.resolve().parents or path.resolve() == UE_INCLUDE_DIR.resolve():
                continue

            try:
                with open(path, "r", encoding="utf-8", errors="ignore") as f:
                    prev_line = ""
                    for line_no, raw_line in enumerate(f, start=1):
                        clean_line = strip_comments_and_strings(raw_line)

                        # Игнорируем директивы препроцессора (#define, #include и т.д.)
                        if clean_line.lstrip().startswith("#"):
                            prev_line = raw_line
                            continue

                        # Игнорируем обертки DEF_SYSCALL
                        if "DEF_SYSCALL" in clean_line:
                            prev_line = raw_line
                            continue

                        for match in call_pattern.finditer(clean_line):
                            func_name = match.group(1)
                            prefix = clean_line[:match.start()]

                            # Проверяем: это объявление/тип или реальный вызов?
                            if is_declaration_or_definition(prefix, prev_line):
                                continue

                            print(f"\033[35m{path.relative_to(cwd)}\033[0m:\033[32m{line_no}\033[0m: "
                                  f"[\033[31;1m{func_name}()\033[0m -> заменить на \033[33;1mue_{func_name}()\033[0m]")
                            print(f"    {raw_line.strip()}\n")
                            matches_count += 1

                        prev_line = raw_line
            except Exception as e:
                print(f"[!] Ошибка при чтении {path}: {e}", file=sys.stderr)

    print(f"Всего реальных вызовов найдено: {matches_count}")

if __name__ == "__main__":
    funcs = get_ue_functions(UE_INCLUDE_DIR)
    search_usages(funcs)