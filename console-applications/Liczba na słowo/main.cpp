#include <iostream>

using namespace std;

int i,j;
string ciag;
void dziesiatki(string n)
{
    if(n[i+1]!='0'&&n[i]=='1')
    {
      switch(n[i+1])
    {
    case '1':cout<<"jedenascie ";         break;
    case '2':cout<<"dwanascie ";      break;
    case '3':cout<<"trzynascie ";      break;
    case '4':cout<<"czternascie ";     break;
    case '5':cout<<"pietnascie ";     break;
    case '6':cout<<"szesnascie ";    break;
    case '7':cout<<"siedemnascie ";   break;
    case '8':cout<<"osiemnascie ";    break;
    case '9':cout<<"dziewietnascie "; break;
    }
    j--;
    i++;
    }
    else
    {
     switch(n[i])
    {
    case '1':cout<<"dziesiec ";         break;
    case '2':cout<<"dwadziescia ";      break;
    case '3':cout<<"trzydziesci ";      break;
    case '4':cout<<"czterdziesci ";     break;
    case '5':cout<<"piecdziesiat ";     break;
    case '6':cout<<"szescdziesiat ";    break;
    case '7':cout<<"siedemdziesiat ";   break;
    case '8':cout<<"osiemdziesiat ";    break;
    case '9':cout<<"dziewiecdziesiat "; break;
    }
    }

}
void jednosci(char znak)
{
    switch(znak)
    {
    case '1':cout<<"jeden ";break;
    case '2':cout<<"dwa ";break;
    case '3':cout<<"trzy ";break;
    case '4':cout<<"cztery ";break;
    case '5':cout<<"piec ";break;
    case '6':cout<<"szesc ";break;
    case '7':cout<<"siedem ";break;
    case '8':cout<<"osiem ";break;
    case '9':cout<<"dziewiec ";break;
    }
}
void setki(char znak)
{
    switch(znak)
    {
    case '1':cout<<"sto ";break;
    case '2':cout<<"dwiescie ";break;
    case '3':cout<<"trzysta ";break;
    case '4':cout<<"czterysta ";break;
    case '5':cout<<"piecset ";break;
    case '6':cout<<"szescset ";break;
    case '7':cout<<"siedemset ";break;
    case '8':cout<<"osiemset ";break;
    case '9':cout<<"dziewiecset ";break;
    }
}
void numbers()
{
    cin>>ciag;
    if(ciag=="0")
        cout<<"zero";
    else
    {
        j=ciag.length();
        while(i++,j--)
        {
            if(j==3||j==6||j==9||j==12||j==0)
               jednosci(ciag[i]);
            else if(j==1||j==4||j==7||j==10||j==13)
                dziesiatki(ciag);
            else if(j==2||j==5||j==8||j==11||j==14)
                setki(ciag[i]);
            if(ciag[i-2]!='0'||ciag[i-1]!='0'||ciag[i]!='0')
            {
                if(j==3)
                cout<<"tys. ";
                if(j==6)
                cout<<"mln. ";
                if(j==9)
                cout<<"mld. ";
                if(j==12)
                cout<<"bln. ";
            }
        }
    }
    cout<<endl;
}
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        i=-1;
        numbers();
    }
    return 0;
}
