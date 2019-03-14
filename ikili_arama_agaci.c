#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct dugum {
        int icerik;
        struct dugum *sol;
        struct dugum *sag;
};


struct ikili_arama_agaci {
        struct dugum *kok;
};
void ikili_arama_agaci_olustur(struct ikili_arama_agaci **agac){
    *agac=(struct ikili_arama_agaci*)malloc(sizeof(struct ikili_arama_agaci));
    if(*agac==NULL) {
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->kok=NULL;
}
bool agac_mi(struct dugum *kok){
	
	if(kok==NULL)return true;
	else if(kok->sag==NULL && kok->sol==NULL)return false;
	else if(kok->icerik<kok->sol->icerik || kok->icerik>kok->sag->icerik){
		return false;
	}
	return agac_mi(kok->sag)+agac_mi(kok->sol);
}
void ekle(struct ikili_arama_agaci *agac,int icerik){
	struct dugum *d,*eklenecek,*geri;
	d=agac->kok;
	eklenecek=(struct dugum*)malloc(sizeof(struct dugum));
	eklenecek->sag=eklenecek->sol=NULL;
	eklenecek->icerik=icerik;
	if(agac->kok==NULL){
		agac->kok=eklenecek;
		return;
	}
	while(d!=NULL){
		geri=d;
		if(icerik<d->icerik){
			d=d->sol;
		}
		else if(icerik>d->icerik){
			d=d->sag;
		}
	}
	if(icerik<geri->icerik){
		geri->sol=eklenecek;
	}
	else{
		geri->sag=eklenecek;
	}
	
}
void inorder_yardimci(struct dugum *kok){

    if(kok==NULL) return;
    inorder_yardimci(kok->sol);
    printf("%4d ",kok->icerik);
    inorder_yardimci(kok->sag);

}

void inorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    inorder_yardimci(agac->kok);
    printf("\n");
}

int dugum_sayisi(struct dugum *kok){
	if(kok==NULL)return 0;
	return 1+dugum_sayisi(kok->sol)+dugum_sayisi(kok->sag);
}
int yaprak_sayisi(struct dugum *kok){
	if(kok==NULL)return 0;
	if(kok->sol==NULL&&kok->sag==NULL)return 1;
	return yaprak_sayisi(kok->sag)+yaprak_sayisi(kok->sol);
}
int ic_dugum(struct dugum *kok){
	if(kok==NULL)return 0;
	if(kok->sag!=NULL|| kok->sol!=NULL){
		return 1+ic_dugum(kok->sol)+ic_dugum(kok->sag);
	}
	else return 0;
}
int derinlik(struct dugum *kok){
	struct dugum *gezen;
	gezen=kok;
	int a,b;
	a=b=0;
	if(gezen==NULL){
		return 0;
	}
	while(gezen->sag!=NULL || gezen->sol!=NULL){
		if(gezen->sag== NULL&&gezen->sol){
			gezen=gezen->sol;
			return 1+derinlik(gezen);
		}
		else if(gezen->sol==NULL&&gezen->sag!=NULL){
			gezen=gezen->sag;
			return 1+derinlik(gezen);
		}
		else if(gezen->sag!=NULL&&gezen->sol!=NULL){
			return 1+derinlik(gezen->sag)+derinlik(gezen->sol);
		
	}
		
}
	if(gezen->sag ==NULL&&gezen->sol==NULL){
		return 0;
	}
}
int main(int argc, char *argv[]) {
	
	struct ikili_arama_agaci *agac=NULL;
    ikili_arama_agaci_olustur(&agac);
	printf(" agac mi=   %d  ",agac_mi(agac->kok));
    ekle(agac,100);
    ekle(agac,50);
    ekle(agac,200);
    ekle(agac,25);
    ekle(agac,75);
    ekle(agac,20);
    ekle(agac,35);
    
    inorder(agac);
    printf("derinlik sayisi= %d ",derinlik(agac->kok));
	printf("dugum sayisi= %d ",dugum_sayisi(agac->kok));
	printf("yaprak sayisi= %d ",yaprak_sayisi(agac->kok));
	printf(" ic dugum sayisi= %d ",ic_dugum(agac->kok));
	printf(" agac mi=   %d  ",agac_mi(agac->kok));
	return 0;
}
