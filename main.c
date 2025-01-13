#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

// Bağli liste düğümünü temsil eden yapinin tanimi
typedef struct Liste {
    int numara;
    char ad[50];
    char soyad[50];
    struct Liste* next;
} dugum;

// İlk ve son düğüm işaretçileri
dugum* ilk = NULL;
dugum* son = NULL;


// Kullanilacak fonksiyonların ön tanımlamaları
void dosyayiOku();
void Listeleme();
void yeni_DugumEkle();
void aramaYap();
void silme(int numara);
void Tasima(int,int);
void dosyayaYaz();

int main() {
    dosyayiOku();
    int secim;
    int numara=0,sira=0;
    while(1){                                               // Menu Tanımlamasi
        printf("\nMenu\n\n1-Listeleme\n2-Ekleme\n3-Arama\n4-Silme\n5-Tasima\n6-Cikis\nSeciminiz : ");
        scanf("%d",&secim);

        switch(secim){
            case 1: // Listeleme Fonksiyonu
                system("cls");
                Listeleme();
                break;
            case 2: // Yeni eklenicek Dugum fonksiyonu
                yeni_DugumEkle();
                system("cls");
                Listeleme();
                break;
            case 3:{
                system("cls");
                aramaYap();
                break;
            }
            case 4:{
                Listeleme();
                printf("\n\nSilmek istediginiz kisinin numarasini giriniz : ");
                scanf("%d",&numara);
                silme(numara);
                break;
            }
            case 5:{
                printf("Lutfen once tasimak istediginiz numarali kisiyi ve hangi siraya tasimak istediginizi yaziniz : ");
                scanf("%d",&numara);
                scanf("%d",&sira);
                Tasima(numara,sira);
                break;
            }
            case 6:{
                printf("Cikis Yapiliyor...\n");
                dosyayaYaz();
                while (ilk != NULL) { // Bellegin temizlenmesi
                    dugum* silinecek = ilk;
                    ilk = ilk->next;
                    free(silinecek);
                }
                    return 0;

            }// Cikis Fonksiyonu
            default:
                system("cls");
                printf("Lutfen 1-6 arasinda deger giriniz... ");
        }
    }
}



void dosyayiOku() {
    FILE* dosya = fopen("veriler.txt", "r"); // Dosyanin Okuma modunda acilmasi
    if (dosya == NULL) {
        printf("Dosya Bulunamadi\n");
        return;
    }

    char satir[100]; 
    while (fgets(satir, sizeof(satir), dosya) != NULL) { // Dosyadaki elemanlarin cekilip bagli listeye aktarilmasi
        int numara;
        char ad[50];
        char soyad[50];
        if (sscanf(satir, "%d#%49[^#]#%49[^#]", &numara, ad, soyad) == 3) {
            dugum* yeni_Dugum = (dugum*)malloc(sizeof(dugum));
            if (yeni_Dugum == NULL) {
                printf("Bellekten Yer Tahsis Edilemedi\n");
                return;
            }
            yeni_Dugum->numara = numara;
            strcpy(yeni_Dugum->ad, ad);
            strcpy(yeni_Dugum->soyad, soyad);
            yeni_Dugum->next = NULL;

            if (ilk == NULL) {
                ilk = yeni_Dugum;
                son = yeni_Dugum;
            } else {
                son->next = yeni_Dugum;
                son = yeni_Dugum;
            }
        }
    }

    fclose(dosya);
}

void Listeleme(){ // Listeleme
    system("cls");
    dugum* temp = ilk;
    if(ilk ==NULL) { // Listede eleman bulunmaması durumu
        printf("\n\nListede herhangi bir eleman bulunamamaktadir... \n");
    }
    else{
        while (temp != NULL) { // Listedeki elemanlarin sırayla yazilmasi
        printf("Numara: %d, Ad: %s, Soyad: %s", temp->numara, temp->ad, temp->soyad);
        temp = temp->next;
    }
    }
}

void yeni_DugumEkle(){ // Kullanici yeni dugum eklemek istediginde çalışan fonksiyon

    char isim[50];
    char soyisim[50];
    int numara;
    dugum *yeni_Dugum = (dugum*)malloc(sizeof(dugum));
    if (yeni_Dugum == NULL) {
                printf("Bellekten Yer Tahsis Edilemedi\n");
                return;
            }
        system("cls");
        printf("Lutfen eklemek istediginiz kisinin bilgilerini giriniz : \n"); //Kisininin bilgilerinin girilmesi 
        printf("Isim : ");
        scanf("%s", isim);

        printf("Soyisim : ");
        scanf("%s", soyisim);
        strcat(soyisim,"\n");
        printf("Numara : ");
        scanf("%d",&numara);


        yeni_Dugum->numara = numara;// Bagli listeye elemanın eklenmesi
        strcpy(yeni_Dugum->ad,isim);
        strcpy(yeni_Dugum->soyad,soyisim);
        
        if (ilk == NULL) {
            ilk = yeni_Dugum;
            son = yeni_Dugum;
            ilk->next = NULL;

        } 
        else {
            son->next = yeni_Dugum;
            son = yeni_Dugum;
            son->next=NULL;
        }
       
        

    


}

void aramaYap() {
    int i=1;
    char soyisim[50];
    printf("Lutfen aramak istediginiz soyisimi giriniz: (buyuk kucuk harflere lutfen dikkat ediniz) ");
    scanf("%s", soyisim);
    strcat(soyisim,"\n");
    dugum *temp = ilk;

    do{
        if (strcmp(soyisim, temp->soyad) == 0) {
            system("cls");
            printf("Numara: %d, Isim: %s, Soyisim: %s\n", temp->numara, temp->ad, temp->soyad);

            char cevap;
            printf("Aramak istenen kayit bulundu mu? (e/h): ");
            scanf(" %c", &cevap);

            if (cevap == 'e' || cevap == 'E') {
                printf("Aranan kayit %d. siradadir.\n", i);
                return; // Arama işlemi sonlandırılır.
            }
            else{
                i++;
                temp= temp->next;
                continue;
            }
        
        }
        i++;
        temp = temp->next;    
    }while (temp != NULL);

    printf("Uzgunuz listede boyle bir kisi bulunmamaktadir \n");
    return;

}

void silme(int numara) {
    dugum* temp = ilk;
    dugum* onceki = NULL;

    // Bağlı listeden silme
    while (temp != NULL){
        if (temp->numara == numara) {
            if (onceki == NULL) {
                // İlk elemanı siliyoruz
                dugum* silinecek = ilk;
                ilk = ilk->next;
                free(silinecek);
                temp = ilk;
                return;
            } else {
                dugum* silinecek = temp;
                onceki->next = temp->next;
                temp = temp->next;
                free(silinecek);
                return;
            }
        } else {
            onceki = temp;
            temp = temp->next;
            continue;
        }
    
    }
    system("cls");
    printf("\n\nBoyle bir kayit bulunamamistir...\n");
}

void Tasima(int numara, int hedefPozisyon) {
    if (numara < 1) {
        printf("Geçersiz numara girdiniz.\n");
        return;
    }

    int pozisyon = 1;
    dugum* temp = ilk;
    dugum* onceki = NULL;
    int boyut = 0;
    while (temp != NULL) {
        boyut++;
        temp = temp->next;
    }
    if(hedefPozisyon>boyut || hedefPozisyon<0){
        printf("Liste boyutu disinda deger girdiniz...\n");
        return;
    }
    temp=ilk;
    // Belirtilen numaradaki düğümü bulma
    while (temp != NULL && temp->numara != numara) {
        onceki = temp;
        temp = temp->next;
    }

    // Belirtilen numara bulunamadıysa
    if (temp == NULL) {
        printf("Belirtilen numaraya sahip kisi bulunamadi.\n");
        return;
    }

    // Belirtilen numaradaki düğümü listeden çıkarma
    if (onceki == NULL) {
        ilk = temp->next;
    } else {
        onceki->next = temp->next;
    }

    // Düğümü hedef pozisyona ekleme
    if (hedefPozisyon == 1) {
        temp->next = ilk;
        ilk = temp;
    } else {
        temp->next = NULL;
        if (ilk == NULL) {
            ilk = temp;
        } else {
            dugum* temp2 = ilk;
            int i = 1;
            while (temp2->next != NULL && i < hedefPozisyon - 1) {
                temp2 = temp2->next;
                i++;
            }
            temp->next = temp2->next;
            temp2->next = temp;
        }
    }
    Listeleme();
}


    
    
   

    

void dosyayaYaz(){

    FILE* gecicidosya = fopen("gecici_veriler.txt", "w"); // Dosyayı açar ve dosyanın sonuna yazar
    dugum* yeni_Dugum = ilk;
    if (gecicidosya != NULL) {
        while(yeni_Dugum != NULL){
        fprintf(gecicidosya, "%d#%s#%s", yeni_Dugum->numara, yeni_Dugum->ad, yeni_Dugum->soyad);
        yeni_Dugum = yeni_Dugum->next;
        }
    }
    fclose(gecicidosya);

    // Eski dosyayı silip, geçici dosyayı yeni dosya olarak adlandırma
    remove("veriler.txt");
    rename("gecici_veriler.txt", "veriler.txt");

}