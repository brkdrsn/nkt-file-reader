#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<dirent.h>
#include <math.h>
#include <ctype.h>
FILE *dosya;
FILE *d1;
FILE *out;
char satir[200];
int swcase;
float x[100000];
float y[100000];
float z[100000];
int r[100000];
int g[100000];
int b[100000];
int hatasay=0;
char dosismi[500];
int nsayac=0;
struct binarydos
{
    float x,y,z;
    int r,g,b;

};


void satiroku(int sn)
{
    int i=0;

    for(i=0; i<=sn; i++)
        fgets(satir,sizeof(satir),dosya);

}

int main(int argc,char * argv[])
{
    float bnrx[1000],bnry[1000],bnrz[1000];

    int bnrr[1000],bnrg[1000],bnrb[1000];

    char temp[200][200];
    DIR *pointer=NULL;
    FILE *dos;
    struct dirent*box;
    pointer=opendir(".");
    int p=0;
    int sayac=0;
    dos=fopen("dosyalar.txt","w");
    box=readdir(pointer);


    while(box!=NULL)
    {

        fputs(box->d_name,dos);
        fputs("\n",dos);
        box=readdir(pointer);

        p++;
    }
    fclose(dos);
    dos=fopen("dosyalar.txt","r");
    while(!feof(dos))
    {

        fscanf(dos,"%s ",&temp[sayac]);
        sayac++;


    }

    char yenidizi[sayac][100];
    char ydout[sayac][100];

    int saysay=0;
    printf("\n");
    for (int h=0; h<sayac; h++)
    {
    if(strcmp(temp[h],"output.nkt")!=0){
        if(strstr(temp[h],".nkt") != NULL)
        {
            strcpy(yenidizi[saysay],temp[h]);
            saysay++;
        }
        else{
            continue;
        }
    }
    }


    char karsilastir[]="ALANLAR x y z r g b\n";
    char karsilastir1[]="ALANLAR x y z\n";
    char data[]="DATA ascii\n";
    char data1[]="DATA binary\n";
    struct binarydos bnr;
    char d[10][200];
    int j=0;
    int i=0;
    int v=0;
    int k=0;
    int result;
    int result1;
    int kontrol=0;
    while(k<saysay)
    {
        out=fopen("output.nkt","a");
        for (int j=0; j<5; j++)
        {
            dosya=fopen(yenidizi[k],"rb");
            satiroku(j);
            strcpy(d[j],satir);
            strcpy(ydout[k],yenidizi[k]);
        }



        char *nokta,*nktsys;

        nokta = strtok(d[3]," ");
        char charnok=nokta;
        nktsys = strtok(NULL," ");
        int noktasay=atoi(nktsys);


        result=strcmp(d[2],karsilastir);
        result1=strcmp(d[2],karsilastir1);
        fprintf(out,"\n*****************************************\n");
        fprintf(out,"Islem yapilan dosya :%s\n",yenidizi[k]);
        fclose(out);
        fprintf(out,"*****************************************\n");
        printf("***********************************************\n");
        printf("Islem yapilan dosya: %s\n",yenidizi[k]);

        if(strcmp(data1,d[4])==0)
        {
            v=0;
            while(!feof(dosya))
            {

                if(j<5)
                {
                    j++;
                }
                else if(result==0)
                {
                    fread(&bnr, sizeof(struct binarydos), 1, dosya);
                    //printf("%f %f %f %d %d %d \n", bnr.x,bnr.y,bnr.z,bnr.r,bnr.g,bnr.b);
                    x[v]=bnr.x;
                    y[v]=bnr.y;
                    z[v]=bnr.z;
                    r[v]=bnr.r;
                    g[v]=bnr.g;
                    b[v]=bnr.b;

                    v++;
                    kontrol++;

                }
                else if(result1==0)
                {
                    fread(&bnr, sizeof(struct binarydos), 1, dosya);
                    //printf("%f %f %f\n", bnr.x,bnr.y,bnr.z);
                    x[v]=bnr.x;
                    y[v]=bnr.y;
                    z[v]=bnr.z;
                    v++;
                    kontrol++;
                }
            }
        }

        else if(strcmp(data,d[4])==0)
        {
            while(!feof(dosya))
            {

                if(j<5)
                {

                    j++;


                }
                else if(result==0)
                {
                    for(int ll=0; ll<saysay; ll++)
                    {
                        r[i]=0;
                        g[i]=0;
                        b[i]=0;
                    }
                    fscanf(dosya,"%f %f %f %d %d %d",&x[i],&y[i],&z[i],&r[i],&g[i],&b[i]);
                    // printf("%f %f %f %d %d %d \n",x[i],y[i],z[i],r[i],g[i],b[i]);
                    i++;
                    kontrol++;
                }
                else if(result1==0)
                {
                    fscanf(dosya,"%f %f %f",&x[i],&y[i],&z[i]);
                    // printf("%f %f %f\n",x[i],y[i],z[i]);
                    i++;
                    kontrol++;
                }
            }
        }
        else

        {
            out=fopen("output.nkt","a");
            fputs("!!!! HATALI DOSYA !!!!\n",out);
            fclose(out);
            printf("HATALI DOSYA \n");
            nsayac++;
            goto hata;
        }


        int wdeger=1;

        while(wdeger)
        {   if(nsayac<saysay){
            printf("1:  Dosya Kontrolu:\n");
            printf("2:  En Yakin/En Uzak Noktalar:\n");
            printf("3:  Kup:\n");
            printf("4:  Kure:\n");
            printf("5:  Nokta Uzakliklari:\n");
            printf("6:  Sonraki Dosya\n");
            printf("***********************************************\n");
            printf("Yapmak istediginiz islemi seciniz: ");
            scanf("%d",&swcase);}
            else{
                goto bitir;
            }



            switch(swcase)
            {
            case 1:
                hatasay=0;
                if(result==0)

                {
                    out=fopen("output.nkt","a");
                    fprintf(out,"***********************************************\n");
                    fclose(out);
                    out=fopen("output.nkt","a");
                    fprintf(out,"SECIM1\n");
                    fclose(out);

                    for(i=0; i<kontrol; i++)
                    {
                        if((g[i]==0 && b[i]==0) )
                        {
                            printf("%d. satirda R G B degerleri eksik.\n",i+1);
                            out=fopen("output.nkt","a");
                            fprintf(out,"%d. satirda R G B degerleri eksik.\n",i+1);
                            fclose(out);
                            hatasay++;
                        }



                    }
                    if(noktasay==kontrol)
                    {
                        out=fopen("output.nkt","a");
                        fprintf(out,"Nokta sayilari dogru\n");
                        fclose(out);
                        printf("Nokta sayilari dogru\n");
                        if(hatasay!=0){
                            goto hata;
                        }
                    }
                    else if(noktasay!=kontrol)
                    {
                        out=fopen("output.nkt","a");
                        fprintf(out,"HATA! %d tane nokta var. dosyada %d adet yaziyor.",kontrol,noktasay);
                        fclose(out);
                        printf("HATA! %d tane nokta var. dosyada %d adet yaziyor.",kontrol,noktasay);
                        printf("\n");
                        printf("***********************************************\n");

                        goto hata;
                    }

                }
                if(result1==0)
                {
                    out=fopen("output.nkt","a");
                    fprintf(out,"***********************************************\n");
                    fclose(out);
                    out=fopen("output.nkt","a");
                    fprintf(out,"SECIM1\n",i+1);
                    fclose(out);
                    if(noktasay==kontrol)
                    {
                        out=fopen("output.nkt","a");
                        fprintf(out,"Nokta sayilari dogru\n");
                        fclose(out);
                        printf("Nokta sayilari dogru\n");
                    }
                    else if(noktasay!=kontrol)
                    {
                        out=fopen("output.nkt","a");
                        fprintf(out,"HATA! %d tane nokta var. dosyada %d adet yaziyor.",kontrol,noktasay);
                        fclose(out);
                        printf("HATA! %d tane nokta var. dosyada %d adet yaziyor.",kontrol,noktasay);
                        printf("\n");
                        printf("***********************************************\n");

                        goto hata;
                    }

                }

                break;


            case 2:
                ;

                int kkayiti,kkayitj,bkayiti,bkayitj;
                float kucuk=300;
                float buyuk=0;
                float sonuc;
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
                        if(sonuc<kucuk && i!=j)
                        {
                            kucuk=sonuc;
                            kkayiti=i;
                            kkayitj=j;
                        }

                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
                        if(sonuc>buyuk && i!=j)
                        {
                            buyuk=sonuc;
                            bkayiti=i;
                            bkayitj=j;
                        }

                    }
                }
                out=fopen("output.nkt","a");
                fprintf(out,"***********************************************\n");
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"SECIM2\n");
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\nEn dusuk fark: %f",kucuk);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\nEn yuksek fark: %f\n",buyuk);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"En dusuk fark, %d ve %d satirdaki noktalar \nEn yuksek fark, %d ve %d satirdaki noktalar\n\n",kkayiti+1,kkayitj+1,bkayiti+1,bkayitj+1);
                fclose(out);
                printf("\nEn dusuk fark :%f", kucuk);
                printf("\nEn yuksek fark:%f", buyuk);
                printf("\nEn dusuk fark, %d ve %d satirdaki noktalar \nEn yuksek fark, %d ve %d satirdaki noktalar\n\n",kkayiti+1,kkayitj+1,bkayiti+1,bkayitj+1);
                break;


            case 3:
                ;
                float xkucuk=300;
                float ykucuk=300;
                float zkucuk=300;
                float xbuyuk=0;
                float ybuyuk=0;
                float zbuyuk=0;
                float fark;
                float enx=x[0];
                float eny=y[0];
                float enz=z[0];
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(x[i]-x[j]);
                        if(sonuc<xkucuk && i!=j)
                        {
                            xkucuk = sonuc;
                        }
                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(x[i]-x[j]);
                        if(sonuc>xbuyuk && i!=j)
                        {
                            xbuyuk = sonuc;
                        }
                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(y[i]-y[j]);
                        if(sonuc<ykucuk && i!=j)
                        {
                            ykucuk = sonuc;
                        }
                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(y[i]-y[j]);
                        if(sonuc>ybuyuk && i!=j)
                        {
                            ybuyuk = sonuc;
                        }
                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(z[i]-z[j]);
                        if(sonuc<zkucuk && i!=j)
                        {
                            zkucuk = sonuc;
                        }
                    }
                }
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        sonuc = fabs(z[i]-z[j]);
                        if(sonuc>zbuyuk && i!=j)
                        {
                            zbuyuk = sonuc;
                        }
                    }
                }
                fark = fabs(x[0]-x[1]);
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        if(i!=j)
                        {
                            if(fark<fabs(x[i]-x[j]))
                                fark=fabs(x[i]-x[j]);
                            if(fark<fabs(y[i]-y[j]))
                                fark=fabs(y[i]-y[j]);
                            if(fark<fabs(z[i]-z[j]))
                                fark=fabs(z[i]-z[j]);
                        }
                    }
                }
                //printf("\n fark :%f\n",fark);
                for(i=0; i<kontrol; i++)
                {
                    if(x[i]<enx)
                        enx=x[i];
                }
                for(i=0; i<kontrol; i++)
                {
                    if(y[i]<eny)
                        eny=y[i];
                }
                for(i=0; i<kontrol; i++)
                {
                    if(z[i]<enz)
                        enz=z[i];
                }
                out=fopen("output.nkt","a");
                fprintf(out,"***********************************************\n");
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"SECIM3\n");
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx,eny,enz);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx+fark,eny,enz);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx,eny+fark,enz);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx,eny,enz+fark);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx+fark,eny+fark,enz);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx+fark,eny,enz+fark);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f",enx,eny+fark,enz+fark);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"\n%f %f %f\n",enx+fark,eny+fark,enz+fark);
                fclose(out);

                printf("\n%f %f %f",enx,eny,enz);
                printf("\n%f %f %f",enx+fark,eny,enz);
                printf("\n%f %f %f",enx,eny+fark,enz);
                printf("\n%f %f %f",enx,eny,enz+fark);
                printf("\n%f %f %f",enx+fark,eny+fark,enz);
                printf("\n%f %f %f",enx+fark,eny,enz+fark);
                printf("\n%f %f %f",enx,eny+fark,enz+fark);
                printf("\n%f %f %f\n",enx+fark,eny+fark,enz+fark);
                break;

            case 4:
                ;

                out=fopen("output.nkt","a");
                fprintf(out,"\n*****************************************\n");
                fprintf(out,"SECIM4\n");
                fclose(out);
                float kurex, kurey, kurez, kurer;
                float k=0;
                printf("\n\nKurenin yaricap x degerini girin :");
                scanf("%f", &kurex);
                printf("\nKurenin yaricap y degerini girin :");
                scanf("%f", &kurey);
                printf("\nKurenin yaricap z degerini girin :");
                scanf("%f", &kurez);
                printf("\nKurenin yaricapini girin :");
                scanf("%f", &kurer);
                out=fopen("output.nkt","a");
                fprintf(out,"kureX: %f\n",kurex);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"kureY: %f\n",kurey);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"kureZ: %f\n",kurez);
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"kureR: %f\n",kurer);
                fclose(out);
                printf("\nKurenin icinde kalan noktalar :\n");
                for(i=0; i<kontrol; i++)
                {
                    for(j=0; j<kontrol; j++)
                    {
                        for(k=0; k<kontrol; k++)
                        {
                            if(i==j && j==k)
                            {
                                if(kurer>sqrt(pow(x[i]-kurex,2)+pow(y[i]-kurey,2)+pow(z[i]-kurez,2)))
                                {
                                    out=fopen("output.nkt","a");
                                    fprintf(out,"%d. Nokta: %f  %f  %f\n", i+1,x[i],y[i],z[i]);
                                    fclose(out);
                                    printf("%d. Nokta: %f  %f  %f\n", i+1,x[i],y[i],z[i]);
                                }

                            }
                        }
                    }
                }

                break;


            case 5:
                ;
                out=fopen("output.nkt","a");
                fprintf(out,"***********************************************\n");
                fclose(out);
                out=fopen("output.nkt","a");
                fprintf(out,"SECIM5\n");
                fclose(out);

                double toplam=0;
                float mesafe;
                double sayac=0;
                float ortalama=0;
                for(i=0; i<kontrol; i++)
                {

                    for(j=(i+1); j<kontrol; j++)
                    {
                        mesafe = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
                        if(i!=j)
                        {
                            toplam = toplam+mesafe;
                            sayac++;
                        }

                    }
                }
                ortalama = toplam/sayac;
                out=fopen("output.nkt","a");
                fprintf(out,"Ortalama uzaklik :%f\n",ortalama);
                fclose(out);
                printf("\nOrtalama uzaklik :%f\n",ortalama);
                break;

            case 6:

                wdeger=0;
                nsayac++;
                break;
            default:
                out=fopen("output.nkt","a");
                fprintf(out,"Hatali deger girdiniz\n");
                fclose(out);
                printf("Hatali deger girdiniz\n");
            }

        }
hata:
        kontrol=0;
        k++;
        i=0;

    }bitir:

    fclose(d1);
    fclose(dosya);
}
