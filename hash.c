#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct CELL {
    char *anahtar;
    struct CELL *next;
};

int lookup(char *anahtar, struct CELL *l){
    if(l==NULL) return 0;
    else if(strcmp(anahtar,l->anahtar)==0) return 1;
    else return lookup(anahtar,l->next);
}

//---------------------------------------------------------------------------//

int insert(char *anahtar, struct CELL **l){
    if(*l==NULL){
        *l=(struct CELL*)malloc(sizeof(struct CELL));
        (*l)->anahtar=(char*)malloc((strlen(anahtar)+1)*sizeof(char));
        strcpy((*l)->anahtar,anahtar);
        (*l)->next=NULL;
        return 1;
    }
    else if(strcmp(anahtar,(*l)->anahtar)) 
        return insert(anahtar, &((*l)->next));
    else return 0;
}

//---------------------------------------------------------------------------//

void print_list(struct CELL *l){
    if(l!=NULL){
        printf("%s ", l->anahtar);
        print_list(l->next);
    }
    
}

//---------------------------------------------------------------------------//

struct table_node{
    int counter;
    struct CELL *header;
};

//---------------------------------------------------------------------------//

struct hash_tablosu{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

//---------------------------------------------------------------------------//

unsigned hash(char *anahtar, int multiplier, int table_size){
    int i=0;
    unsigned int value=0;
    while(anahtar[i]){
        value = (anahtar[i]+multiplier*value)% table_size;
        i++;
    }
    return value;
}

//---------------------------------------------------------------------------//

void initialize_hash_table(struct hash_tablosu **hash_table,int multiplier, int table_size){
    int i;
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   if(*hash_table==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
   }    
    (*hash_table)->tablo_basi=(struct table_node *)malloc(table_size*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
    }
    (*hash_table)->tablo_uzunlugu= table_size;
    (*hash_table)->multiplier= multiplier;
    
    for(i=0; i<table_size; i++){
        ((*hash_table)->tablo_basi+i)->counter = 0;
        ((*hash_table)->tablo_basi+i)->header = NULL;
    }
}
int karsilastir(struct hash_tablosu *hash_table1,struct hash_tablosu *hash_table2){
	int i=0;
	int j=0;
	struct CELL *tablo1,*tablo2;
	if(hash_table1->tablo_uzunlugu!=hash_table2->tablo_uzunlugu)return 0;
	if(hash_table1->multiplier!= hash_table2->multiplier)return 0;
	for(i=0;i<hash_table1->tablo_uzunlugu;i++){
		tablo1=(hash_table1->tablo_basi+i)->header;
		tablo2=(hash_table2->tablo_basi+i)->header;
		if((hash_table1->tablo_basi+i)->counter!=(hash_table2->tablo_basi+i)->counter)return 0;
		for(j=0;j<(hash_table1->tablo_basi+i)->counter;j++){
			if(strcmp(tablo1->anahtar,tablo2->anahtar)==0){
				tablo1=tablo1->next;
				tablo2=tablo2->next;
			}
			else{
				return 0;
			}
		}
	}
	return 1;
}


//---------------------------------------------------------------------------//

void insert_hash_table1(struct hash_tablosu *hash_table,char *anahtar){
    int hash_index=hash(anahtar,hash_table->multiplier,hash_table->tablo_uzunlugu);
    struct CELL *eklenecek;
    eklenecek=(hash_table->tablo_basi+hash_index)->header;
    int a=0;
    while(a==0){
    	if(eklenecek==NULL){
    		eklenecek=(struct CELL*)malloc(sizeof(struct CELL));
    		eklenecek->anahtar=(char*)malloc((strlen(anahtar)+1)*sizeof(char));
    		strcpy(eklenecek->anahtar,anahtar);
    		eklenecek->next=NULL;
    		(hash_table->tablo_basi+hash_index)->counter++;
    		a=1;
		}
		else if(strcmp(anahtar,eklenecek->anahtar)){
			eklenecek=eklenecek->next;
		}
		else return ;
	}
}
void insert_hash_table(struct hash_tablosu *hash_table,char *anahtar){
    int hash_index = hash(anahtar, hash_table->multiplier,
            hash_table->tablo_uzunlugu);
    if(insert(anahtar,&((hash_table->tablo_basi +hash_index)->header)))
     (hash_table->tablo_basi +hash_index)->counter++;
}
//---------------------------------------------------------------------------//

void print_hash_table(struct hash_tablosu *hash_table){
    if(hash_table){
        int index;
        printf("----- HASH TABLOSU -----\n");
        for(index=0; index<hash_table->tablo_uzunlugu; index++){
            printf("%5d : (%2d) ",index,(hash_table->tablo_basi +index)->counter);
            print_list((hash_table->tablo_basi+index)->header);
            printf("\n");
        }
    }
    else printf("Hash Tablosu Bos ...\n");  
}

int main(int argc, char *argv[]) {
	struct hash_tablosu *htable=NULL;
    
    initialize_hash_table(&htable,3,3);
    
    insert_hash_table(htable,"kadayif");
    insert_hash_table(htable,"Trabzonspor");
    insert_hash_table(htable,"kadayif");
    insert_hash_table(htable,"gundogdu");
    insert_hash_table(htable,"besiktas");
    insert_hash_table(htable,"baklava");
    insert_hash_table(htable,"dembaba");
    insert_hash_table(htable,"cardoza");
    struct hash_tablosu *htable1=NULL;
    
    initialize_hash_table(&htable1,3,3);
    
    insert_hash_table(htable1,"kadayif");
    insert_hash_table(htable1,"Trabzonspor");
    insert_hash_table(htable1,"kadayif");
    insert_hash_table(htable1,"gundogdu");
    insert_hash_table(htable1,"besiktas");
    insert_hash_table(htable1,"baklava");
    insert_hash_table(htable1,"dembaba");
    insert_hash_table(htable1,"cardoza");
    printf("karsilastir: %d  ",karsilastir(htable1,htable));
    
   
	return 0;
}
