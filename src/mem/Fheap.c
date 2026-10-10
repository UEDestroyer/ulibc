#include "mem/Fheap.h"

#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define SIZE (1024 * 1024)



static struct BlockHeader* first = NULL;

static void* getNewSize(size_t size){
    if (size > SIZE_MAX - sizeof(BlockHeader) - ALIGNMENT){return NULL;}
    size_t reqSize = SIZE;
    if (size + sizeof(BlockHeader)> SIZE ){
        reqSize=ALIGN(size + sizeof(BlockHeader));
    }
    BlockHeader* header = mmap(NULL,reqSize,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (header==MAP_FAILED){
        return NULL;
    }

    header->size = ALIGN(size);
    header->is_free = false;
    header->next = NULL;
    header->end = ((char *)header) + reqSize;

    return header ;
}

void Ffree(void* ptr){
    if (ptr == NULL || first == NULL){
        return;
    }
    BlockHeader* header = ((BlockHeader*) ptr) - 1 ;

    if (header->size + sizeof(BlockHeader) >=SIZE){
        if (first != header){
            BlockHeader* curr = first;
            
            while ( curr != NULL && curr->next != header ){
                curr = curr->next; 
            }
            if (curr != NULL){
                curr->next = header->next;
            }
        }else {
            first = header->next;
        }
        munmap(header,ALIGN(header->size +sizeof(BlockHeader)));

    } else {
        header->is_free = true;
        
        BlockHeader* up = header->next;
        BlockHeader* prev = header;
        while (up!=NULL && (char*)prev + prev->size + sizeof(BlockHeader) == (char *)up && up->is_free && up->end == prev->end){
            prev->size +=up->size + sizeof(BlockHeader);
            prev->next = up->next;
            up = up->next;
        }

    }



    return;
}

void* Fmalloc(size_t size){
    if (size ==0){
        return NULL;
    }
    if (size > SIZE_MAX - sizeof(BlockHeader) - ALIGNMENT){return NULL;}
    BlockHeader* prev = NULL;
    BlockHeader* curr = NULL;
    BlockHeader* block = NULL;



    if (first == NULL){
        first = getNewSize(size);
        block = first;
        return block != NULL ? (block + 1) : NULL;
    }else {
        curr=first;
        while (curr!=NULL){
            if (curr->is_free && curr->size>=ALIGN(size)){
                if (ALIGN(size) + sizeof(BlockHeader)< curr->size && curr->size - ALIGN(size) - sizeof(BlockHeader) > ALIGNMENT ){
                    BlockHeader* nw =(BlockHeader*) ((char *)curr + ALIGN(size) + sizeof(BlockHeader));

                    nw->size = curr->size - ALIGN(size) - sizeof(BlockHeader);
                    nw->end = curr->end;
                    nw->is_free = true;
                    nw->next = curr->next;

                    curr->size = ALIGN(size);
                    curr->next = nw;

                }
                curr->is_free = false;
                break;
            }
            prev=curr;
            curr=prev->next;
        }
        block = curr;
    }
    if (block == NULL && prev!=NULL && (char *)prev->end - ((char *)prev + sizeof(BlockHeader) + prev->size) >=ALIGN(size) + sizeof(BlockHeader)){
        block =(BlockHeader*) ((char *)prev + prev->size + sizeof(BlockHeader));
        block->size = ALIGN(size);
        block->end = prev->end;
        block->is_free = false;
        block->next = NULL;
    }else if (block == NULL){
        block = getNewSize(size);
    }
    if (prev != NULL){
        prev->next = block;
    }



    return block != NULL ? (block + 1) : NULL;
}

void* Fcalloc(size_t nmemb,size_t size){
    if (nmemb!=0 && size >SIZE_MAX / nmemb){
        return NULL;
    }
    void* ptr = Fmalloc(nmemb * size);
    if (ptr==NULL){
        return NULL;
    }
    memset(ptr,0,nmemb*size);
    return ptr;
}
void* Frealloc(void* ptr, size_t size){
    if (size == 0){
        Ffree(ptr);return NULL;
    }
    if (ptr==NULL){
        return Fmalloc(size);
    }

    void* nptr=Fmalloc(size);

    if (nptr==NULL){
        return NULL;
    }

    BlockHeader* header = ((BlockHeader*) ptr)-1;
    size_t uSize = min(size,header->size);

    memcpy(nptr,ptr,uSize);
    Ffree(ptr);
    

    return nptr;

}
void *Freallocarray(void *ptr, size_t nmemb, size_t size){
    size_t bytes;
    if (__builtin_mul_overflow(nmemb, size, &bytes)){
        return NULL;
    }
    return Frealloc(ptr,nmemb * size);
}