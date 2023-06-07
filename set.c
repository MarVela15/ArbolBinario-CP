
#include <stdlib.h>
#include <stdio.h>
#include "set.h"

/* Funciones para el manejo de los árboles */

int tree_insert(struct STRTNODE **root,TYPE e,COMPAREFUNC cf)
{
	int inserted = 0;
	if(*root==NULL)
	{
		*root = malloc(sizeof(struct STRTNODE));
		(*root)->elem = e;
		(*root)->left = NULL;
		(*root)->right = NULL;
		inserted = 1;
	}
	else if(cf(e,(*root)->elem)<0)  // e < (*root)->elem
		inserted = tree_insert(&(*root)->left,e,cf);
	else if(cf(e,(*root)->elem)>0)  // e > (*root)->elem
		inserted = tree_insert(&(*root)->right,e,cf);

	return inserted;
}


void tree_print(int level,struct STRTNODE *root,PRINTFUNC pf)
{
	int i;
	if(root!=NULL)
	{
		tree_print(level+1,root->right,pf);

		for(i=0;i<level;i++)
			printf("\t");
		pf(root->elem);

		tree_print(level+1,root->left,pf);
	}
}


SET set_create(COMPAREFUNC cf,PRINTFUNC pf)
{
	SET new_set = malloc(sizeof(struct STRSET));
	new_set->tree_root = NULL;	//Inicia con el árbol vacío
	new_set->size = 0;
	new_set->cf = cf;
	new_set->pf = pf;

	return new_set;
}

void set_add(SET set,TYPE e)
{
	if(tree_insert(&set->tree_root,e,set->cf))
		set->size = set->size + 1;
}

int set_size(SET set)
{
	return set->size;
}

void set_print(SET set)
{
	tree_print(0,set->tree_root,set->pf);
}
//Funcion auxiliar del set remove para borrar los nodos
void node_remove(struct STRTNODE **root, TYPE e, COMPAREFUNC cf)
{
    if (*root == NULL) {
        // Si el nodo está vacío, no hay nada que hacer.
        return;
    }
    //Comparar el elemento buscado con el del  nodo para saber donde encontrarlo
    int comp_result = cf(e, (*root)->elem);

    if (comp_result < 0) {
        // Si e es menor que el elemento actual, buscar en el subárbol izquierdo, esto se hace utilizando la recursividad.
        node_remove(&((*root)->left), e, cf);
    } else if (comp_result > 0) {
        // Si e es mayor que el elemento actual, buscar en el subárbol derecho, esto se hace utilizando la recursividad.
        node_remove(&((*root)->right), e, cf);
    } else {
        // Si encontramos el elemento a eliminar.

        // Verificar si tiene un solo hijo o ninguno.
        if ((*root)->left == NULL) {
            struct STRTNODE *temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            struct STRTNODE *temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            // Si el nodo tiene dos hijos, buscar el elemento más a la izquierda del subárbol derecho.
            struct STRTNODE *temp = (*root)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }

            // Intercambiar los valores entre el nodo actual y el nodo más a la izquierda del subárbol derecho.
            (*root)->elem = temp->elem;

            // Eliminar el nodo más a la izquierda del subárbol derecho, utilizando recursividad.
            node_remove(&((*root)->right), temp->elem, cf);
        }
    }
}

//Esta es la funcion remove la cual manda llamar la funcion auxiliar
void set_remove(SET set, TYPE e)
{
  //Se le dan los parametros necesaros que es la direccion del apuntador al arbol, el elemento a eliminar y la funcion para comparar
    node_remove(&(set->tree_root), e, set->cf);
  //Resta 1 al tamaño
    set->size--;
}
