#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct hucre {
        int icerik;
        struct hucre *sonraki;
};
int siralimi(struct hucre **liste_basi){
	struct hucre *gezen,*kontrol;
	gezen=*liste_basi;
	kontrol=(*liste_basi)->sonraki;
	while(gezen!=NULL){
		while(kontrol!=NULL){
			if(gezen->icerik>kontrol->icerik){
				return 0;
			}
			kontrol=kontrol->sonraki;	
		}
		gezen=gezen->sonraki;
		if(gezen->sonraki==NULL){
			return 1;
		}
		kontrol=gezen->sonraki;
		
			
	}
	return 1;
}
void liste_basina_ekle(int icerik,struct hucre **liste_basi){
	struct hucre *yeni;
	yeni=(struct hucre*)malloc(sizeof(struct hucre));
	yeni->icerik=icerik;
	yeni->sonraki=*liste_basi;
	*liste_basi=yeni;
}
void liste_yaz_r(struct hucre *liste_basi){
	if(liste_basi!=NULL){
		printf("%d ",liste_basi->icerik);
		return liste_yaz_r(liste_basi->sonraki);
	}
}
void tersten_listeyaz_recursive(struct hucre *liste_basi) {
    if(liste_basi != NULL) {
        tersten_listeyaz_recursive(liste_basi->sonraki);
        printf("%d ", liste_basi->icerik);
    }
}
void liste_sonuna_ekle(int icerik,struct hucre **liste_basi){
	struct hucre *yeni,*a;
	yeni=(struct hucre*)malloc(sizeof(struct hucre));
	yeni->icerik=icerik;
	yeni->sonraki=NULL;
	if(liste_basi==NULL){
		yeni->sonraki=*liste_basi;
		*liste_basi=yeni;	
	}
	else{
		a=*liste_basi;
		while(a->sonraki!=NULL){
			a=a->sonraki;
		}
		a->sonraki=yeni;
	}
}
void en_kucuk_sil(struct hucre **liste_basi){
	struct hucre *enkucuk,*onceki,*gezen;
	enkucuk=*liste_basi;
	gezen=(*liste_basi)->sonraki;
	onceki=*liste_basi;
	while(gezen!=NULL){
		if(gezen->icerik<enkucuk->icerik){
			enkucuk=gezen;
			gezen=gezen->sonraki;			
		}
		
		else{
			onceki=gezen;
			gezen=gezen->sonraki;
			
		}
	}
	if(enkucuk==*liste_basi){
		*liste_basi=(*liste_basi)->sonraki;
		free(enkucuk);
	}
	else{
		onceki->sonraki=enkucuk->sonraki;
		free(enkucuk);
	}
}
void liste_sirali_ekle1(int icerik, struct hucre **liste_basi) {
        struct hucre *a, *b, *eklenen;
        b = *liste_basi;
        while(b != NULL && b->icerik <= icerik) {
            a = b;
            b = b->sonraki;
        }
        eklenen = (struct hucre*)malloc(sizeof(struct hucre));
        eklenen->icerik=icerik;
        eklenen->sonraki=NULL;
        if (b == *liste_basi) {
            eklenen->sonraki = *liste_basi;
            *liste_basi = eklenen;
        }
        else {
            a->sonraki = eklenen;
            eklenen->sonraki = b;
        }
}
void liste_sirali_ekle(int icerik,struct hucre **liste_basi){
	struct hucre *yeni,*a,*b,*c;
	yeni=(struct hucre*)malloc(sizeof(struct hucre));
	yeni->icerik=icerik;
	yeni->sonraki=NULL;
	a=*liste_basi;
	if(a==NULL){
		yeni->sonraki=*liste_basi;
		*liste_basi=yeni;
		return;
	}
	while(a!=NULL && a->icerik<=icerik){
		b=a;
		c=a->sonraki;
		a=a->sonraki;
	}
	b->sonraki=yeni;
	yeni->sonraki=c;
}
void liste_eleman_sil(int silinen, struct hucre **liste_basi) {
	struct hucre *temp,*onceki,*a;
	a=*liste_basi;
	while(a!=NULL && a->icerik!=silinen){
		onceki=a;
		a=a->sonraki;
	}
	if(a==NULL){
		return;
	}
	else if(a==*liste_basi){
		temp=liste_basi;
		*liste_basi=(*liste_basi)->sonraki;
		free(temp);
		return;
	}
	else{
		temp=a;
		onceki->sonraki=temp->sonraki;
		free(temp);
		
	}
}
void liste_ters_cevir(struct hucre **liste_basi){
	struct hucre *a,*b;
	a=NULL;
	while(*liste_basi!=NULL){
		b=*liste_basi;
		*liste_basi=(*liste_basi)->sonraki;
		b->sonraki=a;
		a=b;
	}
	*liste_basi=a;
}

int main(int argc, char *argv[]) {
	struct hucre *liste1 = NULL;
	liste_basina_ekle(50, &liste1);
    liste_basina_ekle(60, &liste1);
	liste_sirali_ekle1(16, &liste1);
    liste_sirali_ekle1(13, &liste1);
    liste_sirali_ekle1(45, &liste1);
    liste_sirali_ekle1(73, &liste1);
    liste_sirali_ekle1(99, &liste1);
    liste_sirali_ekle1(57, &liste1);
    liste_sirali_ekle1(39, &liste1);
     liste_yaz_r(liste1);
     printf("\n");
  en_kucuk_sil(&liste1);
    liste_yaz_r(liste1);
    int sayi, rakam, toplam = 0;
	printf("\nBir Sayi Giriniz : ");
	scanf("%i", &sayi);
	while(sayi > 0) {
		rakam = sayi % 10;
		toplam = toplam + rakam;
		sayi = sayi / 10;
	}
	printf("\nSayidaki rakamlarin toplami : %i", toplam);
   // printf("sirali mi==  %d  ",siralimi(&liste1));
    //ste_eleman_sil(13, &liste1);
   ///ste_eleman_sil(7, &liste1);
   //iste_yaz_r(liste1);
    //liste_ters_cevir(&liste1);
    //liste_yaz_r(liste1);
	return 0;
}
