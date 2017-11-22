#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"
#define INITIAL_VALUE 10
#define INCREMENT 10

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);


//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux=NULL;
    void** auxpElements;
    this = (ArrayList*)malloc(sizeof(ArrayList));
    if(this !=NULL)
    {
        auxpElements=(void**)malloc(sizeof(void*)*INITIAL_VALUE);
    }
    if(auxpElements !=NULL)
    {
        this->size=0;
        this->pElements=auxpElements;
        this->reservedSize=INITIAL_VALUE;
        this->add=al_add;
        this->len=al_len;
        this->set=al_set;
        this->remove=al_remove;
        this->clear=al_clear;
        this->clone=al_clone;
        this->get=al_get;
        this->contains=al_contains;
        this->push=al_push;
        this->indexOf=al_indexOf;
        this->isEmpty=al_isEmpty;
        this->pop=al_pop;
        this->subList=al_subList;
        this->containsAll=al_contains;
        this->deleteArrayList=al_deleteArrayList;
        this->sort=al_sort;

        returnAux=this;
    }
    else
    {
        free(this);
    }
    return returnAux;

}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this,void* pElement)
{
    int returnAux=-1;

    if(this !=NULL && pElement !=NULL)
    {
        if(!(resizeUp(this)))
        {
            this->pElements[this->size]=pElement;
            this->size++;
            returnAux = 0;

        }

    }

    return returnAux;

}



/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int aux=-1;
    if(this!=NULL)
    {
        free(this->pElements);
        free(this);
        aux=0;
    }
    return aux;
}



/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int tam=-1;
    if(this!=NULL)
    {
        tam = this->size;
    }

    return tam;
}



/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* aux=NULL;
    if(this!=NULL && index>=0 && index<this->size)
    {
        aux=this->pElements[index];

    }
    return aux;
}




/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    // se puede usar un flag//
    int aux=-1;
    int i;
    if(this!=NULL && pElement!=NULL)
    {
        aux=0;
        for(i=0; i<this->size; i++)
        {
            if(pElement == *(this->pElements + i))
            {
                aux=1;
                break;
            }

        }

    }

    return aux;
}


/** \brief  Set a element in This at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux=-1;
    int aux;
    if(this!=NULL && index>=0 && index<=this->size && pElement!=NULL)
    {
        if(this->size==index)
        {
            aux = this->add(this,pElement);
            if(!aux)
            {
                returnAux=0;
            }
        }
        else
        {
            this->pElements[index]=pElement;
            returnAux=0;
        }

    }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux=-1;
    if(this!=NULL && index>=0 && index<this->size)
    {
        if(!contract(this,index))
        {
            returnAux=0;
        }
    }


    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux=-1;
    if(this!=NULL)
    {
        free(this->pElements);
        this->size=0;
        this->reservedSize=INITIAL_VALUE;
        returnAux=0;
    }


    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* clone=al_newArrayList();
    // void** aux;
    int i;

    if(this!=NULL && clone!=NULL)
    {
        /* aux=(void**)realloc(clone->pElements,sizeof(void*)*this->reservedSize);
         if(aux!=NULL)
         {
             clone->pElements=aux;
             free(aux);
          */
        for(i=0; i<this->size; i++)
        {
            this->add(clone,this->get(this,i));

        }
    }

    else
    {
        clone = NULL;

    }

    return clone;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && pElement!=NULL && index>=0 && index<=this->size)
    {

        if(!expand(this,index))
        {
            this->pElements[index]=pElement;
            returnAux=0;
        }

    }

    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnIndex = -1;
    int i;
    if(this!=NULL && pElement!=NULL)
    {
        for(i=0; i<this->size; i++)
        {
            if(this->pElements[i] == pElement)
            {
                returnIndex = i;
                break;

            }
        }
    }

    return returnIndex;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux=-1;
    if(this!=NULL)
    {
        if(this->size >0)
        {
            returnAux=0;
        }
        else
        {
            returnAux=1;
        }
    }


    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL && index>=0 && index<this->size)
    {
        returnAux=this->get(this,index);
        this->remove(this,index);
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{

    ArrayList* aux=NULL;
    void* auxPelement;
    int i;
    if(this!=NULL && from>=0 && from<this->size && to<=this->size && to>from )
    {
        aux=al_newArrayList();
        if(aux!=NULL)
        {
            for(i=from; i<to; i++)
            {
                auxPelement= this->get(this,i);
                if(auxPelement!=NULL)
                {
                    //    aux->add(aux,*(this->pElements+i));
                    aux->add(aux,this->get(this,i));

                }

            }

        }


    }

    return aux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)

{
    int returnAux=-1;
    int i;
    if(this!=NULL && this2!=NULL)
    {
        if(this->size==this2->size)
        {
            for(i=0;i<this->size;i++)
            {
                if((al_contains(this,al_get(this2,i)))==1)
                {
                    returnAux=1;

                }
                else
                {
                    returnAux=0;
                    break;
                }
            }
        }
        else
        {
            returnAux=0;
        }
    }

    return returnAux;

}
/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order)
{
    int ordenamiento;
    void* aux;
    int j;
    int i;
    int returnAux=-1;

    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {
        for(i=0; i<this->size-1; i++)
        {
            for(j=i+1; j<this->size; j++)
            {
                ordenamiento = pFunc(this->get(this,i),this->get(this,j));
                if(order==1 && ordenamiento==1)
                {
                    aux = *(this->pElements + i);
                    *(this->pElements + i)= *(this->pElements + j);
                    *(this->pElements + j)= aux;

                }
                else if(order==0 && ordenamiento==-1)
                {
                     aux = *(this->pElements + i);
                    *(this->pElements + i)= *(this->pElements + j);
                    *(this->pElements + j)= aux;

                }
            }
        }

        returnAux=0;
    }
    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* pList)
{
    int returnAux=-1;
    void** aux;
    if(pList !=NULL )
    {
        if(pList->size == pList->reservedSize)
        {
            aux=(void**)realloc(pList->pElements,sizeof(void*)*(pList->reservedSize+INCREMENT));
            if(aux!=NULL)
            {
                pList->pElements=aux;
                pList->reservedSize = pList ->reservedSize + INCREMENT;
            }
        }
        returnAux=0;
    }
    return returnAux;
}



/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux=-1;
    int i;
    if(this!=NULL)
    {

        if(!resizeUp(this))
        {
            for(i=this->size; i>index; i--)
            {
                this->pElements[i]=this->pElements[i-1];
            }
            this->size ++;
            returnAux=0;
        }

    }
    return returnAux;
}




/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux=-1;
    int i;
    if(this!=NULL)
    {
        for(i=index; i<this->size; i++)
        {
            this->pElements[i]= this->pElements[i+1];

        }
        this->size--;
        returnAux=0;

    }
    return returnAux;

}

/** \brief Decrement the number of elements in This in AL_INCREMENT elements.
 * \param This ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [This is NULL pointer ]
 *                  - (0) if ok
 */
int resizeDown(ArrayList* this)
{
    int returnAux=-1;
    if(this!=NULL )
    {
        if((this->reservedSize - this->size) >INCREMENT)
        {
            this->pElements=(void**)realloc(this->pElements,sizeof(void*)*(this->reservedSize-INCREMENT));
            this->reservedSize = this->reservedSize - INCREMENT;
        }
        returnAux=0;
    }
    return returnAux;
}
