////			Приложение 08
//// Пример разработки класса для представления объектов типа "загородный дом"
//#include "array"
//#include <stdio.h>
//#include <string.h>
//
//int IsRazd(char sym, char *razd)
//{
//    for(int i=0;razd[i];i++)
//        if(razd[i]==sym)
//            return 1;
//    return 0;
//}
//
//char* StrTok(char *str, char *razd)
//{
//    static char *p,word[100];  int i=0,state=1;
//
//    if(str)  p=str;
//    while(1)
//    {
//        switch(state)
//        {
//            case 1:
//                if(*p=='\0')          return NULL;
//                if(IsRazd(*p,razd))  {p++; break;}
//                state=2;
//            case 2:
//                if(*p=='\0' || IsRazd(*p,razd))   {word[i]='\0'; return word;}
//                word[i++]=*p++;
//        }
//    }
//}
//
//class VilHouse
//{
//    MString Region, Village, Type;
//    Array<MString> AddInf;
//    float Square, Area, Price;
//public:
//    VilHouse(char* Region, char* Village, char* Type,
//             char* AddInf,float Square, float Area, float Price);
//    VilHouse( const VilHouse &);
//    VilHouse & operator=  (const VilHouse &);
//    friend ostream& operator<<(ostream &, const VilHouse &);
//    void CorrectAll(char* region, char* village, char* type,
//                    char* addInf,float square, float area, float price);
//    MString* StringMember(char* Name);
//    float* FloatMember(char* Name);
//    void GetAddinf(Array<MString> &ar);
//
//
//    //----------------It must be write -----------------------------
//    void AddAddInf(char* NewRecord);
//    void CorrectAddInf(int NumberRecord, char* NewRecord=NULL);
//    //="" it is delete Record of AddInf with number equal NumberRecord
//};
//Region
////VilHouse::VilHouse(char* region="", char* village="",
////                   char* type="", char* addinf="", float square=0.0,
////                   float area=0.0, float price=0.0):
////        Region(region),Village(village),Type(type),
////        Square(square),Area(area),Price(price)
////{
////    char *p;
////    if(p=StrTok(addinf,";"))
////    {
////        AddInf.Add(p);
////        while(p=StrTok(NULL,";"))
////            AddInf.Add(p);
////    }
////}
////
////VilHouse & VilHouse::operator=(const VilHouse &vh)
////{
////    Region = vh.Region;
////    Village= vh.Village;
////    Type   = vh.Type;
////    AddInf = vh.AddInf;
////    Square = vh.Square;
////    Area   = vh.Area;
////    Price  = vh.Price;
////    return *this;
////}
////
////VilHouse VilHouse::VilHouse(const VilHouse &vh)
////{
////    Region = vh.Region;
////    Village= vh.Village;
////    Type   = vh.Type;
////    AddInf = vh.AddInf;
////    Square = vh.Square;
////    Area   = vh.Area;
////    Price  = vh.Price;
////}
////
////ostream& operator<<(ostream &c, const VilHouse &vh)
////{
////    int size,i=0;
////    c<<"Place:  "<<vh.Region<<", "<<vh.Village<<endl;
////    c<<"Type:   "<<vh.Type<<endl;
////    c<<"Square: "<<vh.Square<<", "<<vh.Area<<endl;
////    if(size=vh.AddInf.Size())
////    {
////        c<<"AddInf: ";
////        for(;i<size;i++)
////            c<<i<<") "<<vh.AddInf[i]<<"  ";
////        c<<endl;
////    }
////    c<<"Price:  "<<vh.Price;
////    return c;
////}
////
////void  VilHouse::CorrectAll(char* region, char* village, char* type,
////                           char* addinf,float square, float area, float price)
////{
////    if(strcmp(region,"-"))
////        Region = MString(region);
////    if(strcmp(village,"-"))
////        Village = MString(village);
////    if(strcmp(type,"-"))
////        Type = MString(type);
////    if(strcmp(addinf,"-"))
////    {
////        char *p;
////        AddInf.Clear();
////        if(p=StrTok(addinf,";"))
////        {
////            AddInf.Add(p);
////            while(p=StrTok(NULL,";"))
////                AddInf.Add(p);
////        }
////    }
////    if(square!=0)
////        Square = square;
////    if(area!=0)
////        Area   = area;
////    if(price!=0)
////        Price  = price;
////}
////
////MString*  VilHouse::StringMember(char* Name)
////{
////    if(!strcmp(Name,"Region"))
////        return &Region;
////    if(!strcmp(Name,"Village"))
////        return &Village;
////    if(!strcmp(Name,"Type"))
////        return &Type;
////    return NULL;
////}
////
////float*  VilHouse::FloatMember(char* Name)
////{
////    if(!strcmp(Name,"Square"))
////        return &Square;
////    if(!strcmp(Name,"Area"))
////        return &Area;
////    if(!strcmp(Name,"Price"))
////        return &Price;
////    return NULL;
////}
////
////void VilHouse::GetAddinf(Array<MString> &ar)
////{
////    for(int i=0;i<AddInf.Size();i++)
////        ar.Add(AddInf[i]);
////}
//
//void main(void)
//{
//    char AddInf[]="Water yes;For station 2km;For lake 100m;For river 1km";
//    VilHouse vh1("Hriozerski region","Orexovo",
//                 "Stone","Water yes;For station 2km;For lake 100m;For river 1km",60, 10.5, 40000);
//    cout<<vh1<<endl;
//    VilHouse vh2("Hriozerskii","67 km","Stone","",60,10.5,40000);
//    cout<<vh2<<endl;
//    cout<<"------------------"<<endl;;
//    getch();
//    VilHouse vh3;
//    vh3=vh2=vh1;
//    cout<<vh3<<endl;
//    cout<<"------------------"<<endl;
//    getch();
//    VilHouse vh4(vh3);
//    vh3.CorrectAll("-", "Lembolovo", "-","Boot",0, 0, 0);
//    cout<<vh1<<endl;
//    cout<<vh2<<endl;
//    cout<<vh3<<endl;
//    cout<<vh4<<endl;
//    cout<<"------------------"<<endl;
//    getch();
//    vh1.CorrectAll("Gatchinski region","Sumino","-","MMMMMM;NNNN",0,11.5,37000);
//    cout<<vh1<<endl;
//    cout<<"------------------"<<endl;
//    getch();
//    *vh1.StringMember("Region")=string("Kirovski reg");
//    *vh1.FloatMember("Price")=70000;
//    cout<<vh1<<endl;
//    cout<<*vh1.StringMember("Region");
//    getch();
//}
