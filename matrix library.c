#include<stdio.h>

int main(){
    FILE *infile = fopen("input.txt", "r");
    FILE *outfile = fopen("output.txt","w");

    long year; //      preparation         //
    fscanf(infile,"%d",&year);
    double credit, perc;
    fscanf(infile,"%f%f",&perc,&credit);
    long months = year*12;
    //printf("year %d percent %d credit %.2f \n",year,perc,credit);
    //printf("%d %.2f %.2f\n ",year,perc, credit);
    long res = -1; long fix_credit = credit;
    long l = 0; long r = credit+1;
    long max_c_pay = -1;

    while (l != r) {
        long c_pay = 0;
        long fix;
        credit = fix_credit;
        long pay = (l+r)/2;
        long c_oper = 0;
        //printf("%.2f - %d\n ", credit,pay);

        for (int i = 0; i < months; i++) {
            //printf("i=%d %.2f ",i, credit);
            fix = (long)((credit-pay)*((perc/100)+1));
            credit = ((credit-pay)*((perc/100)+1));
            c_oper++;
            c_pay = i+1;
            //printf(" == %.2f \n", credit);
            if (credit > fix)
                credit = fix+1;
            if (credit <= 0) {
                c_pay = i+1;
                break;
            }
            if (credit >= fix_credit) {
                break;
            }
        }
        if (credit>0 || c_oper <= 1){
            l = pay+1;
            if (fix_credit == 1)
                res = pay;
        }
        else{
            r = pay;
            if (max_c_pay < c_pay)
                max_c_pay = c_pay;
            res = pay;
        }
    }

    printf("%d",res);
    fprintf(outfile,"%d",res);

    return 0;
}