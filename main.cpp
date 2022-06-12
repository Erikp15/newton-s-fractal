#include <bits/stdc++.h>
#include "graphics.h"

using namespace std;

typedef long long ll;
typedef long double ld;

class point{
public:
    ld x,i;
};


const ll Sizex=640,Sizey=480;
ld max_root_distance=0;

map<ll,ll> choice_2_size,root_2_color;

complex<ld> calc_transition(complex<ld> p,ll choice){
    complex<ld> ans;
    complex<ld> der;
    /*
    //x^3-1 old
    ans.x=pow(p.x,3)-3*pow(p.i,2)*p.x-1;
    ans.i=3*pow(p.x,2)*p.i-pow(p.i,3);
    der.x=3*pow(p.x,2)-3*pow(p.i,2);
    der.i=6*p.x*p.i;
    */
    // x^3-1
    if(choice==0){
        ans=pow(p,3)-complex<ld>(1);
        der=complex<ld>(3)*pow(p,2);
    }
    //x^3-2.55x^2-1
    if(choice==1){
        ans=pow(p,3)-complex<ld>(2.55)*pow(p,2)-complex<ld>(1);
        der=complex<ld>(3)*pow(p,2)-complex<ld>(5.1)*p;
    }
    // x^5+x^2-x+1
    if(choice==2){
        ans=pow(p,5)+pow(p,2)-p+complex<ld>(1);
        der=complex<ld>(5)*pow(p,4)+complex<ld>(2)*p-complex<ld>(1);
    }
    // x^9-1
    if(choice==3){
        ans=pow(p,9)-complex<ld>(1);
        der=complex<ld>(9)*pow(p,8);
    }
    // x^8-x^6+x^4-x^2+1
    if(choice==4){
        ans=pow(p,8)-pow(p,6)+pow(p,4)-pow(p,2)+complex<ld>(1);
        der=complex<ld>(8)*pow(p,7)-complex<ld>(6)*pow(p,5)+complex<ld>(4)*pow(p,3)-complex<ld>(2)*p;
    }
/*
    //x^3-2.55x^2-1
    ans.x=pow(p.x,3)-3*pow(p.i,2)*p.x-2.55*pow(p.x,2)+2.55*pow(p.i,2)-1;
    ans.i=3*pow(p.x,2)*p.i-pow(p.i,3)-5.1*p.x*p.i;
    der.x=3*pow(p.x,2)-3*pow(p.i,2)-5.1*p.x;
    der.i=6*p.x*p.i-5.1*p.i;
    */
    //ans.x=(ans.x*der.x+ans.i*der.i)/(pow(der.x,2)+pow(der.i,2));
    //ans.i=(ans.i*der.x-ans.x*der.i)/(pow(der.x,2)+pow(der.i,2));
    return ans/der;
}

void draw_pretty_pixel(ll x,ll y,ll col1, ld col2);

// horrible code - mainly having fun with pairs
pair<ll,ld> calc_closest(complex<ld> p,complex<ld> roots[],ll s){
    pair<ld,ll> ans; // ld is first since comparison (min) on pair uses .first
    ans.first=1e18;
    ans.second=1e18;
    ld total=0.001;

    for(ll i=0;i<s;i++){
        ld dist = sqrt(pow((real(p)-real(roots[i])),2)+pow((imag(p)-imag(roots[i])),2));
        total+=dist;
        ans=min(ans,{dist,i});
    }
    return {ans.second,  ans.first/max_root_distance};
}

int rgb2root[10][3];
int main(){
    int gdriver = DETECT, gmode, errorcode;
    complex<ld> roots[10][10];
    roots[0][0]=complex<ld>(1,0);
    roots[0][1]=complex<ld>(-0.5,-0.86602540378443864676372317075294);
    roots[0][2]=complex<ld>(-0.5,0.86602540378443864676372317075294);
    roots[1][0]=complex<ld>(2.68836,0);
    roots[1][1]=complex<ld>(-0.0691821,-0.60596);
    roots[1][2]=complex<ld>(-0.0691821,0.60596);
    roots[2][0]=complex<ld>(-2.3247,0);
    roots[2][1]=complex<ld>(0,-1);
    roots[2][2]=complex<ld>(0,1);
    roots[2][3]=complex<ld>(0.66236,-0.56228);
    roots[2][4]=complex<ld>(0.66236,0.56228);
    roots[3][0]=complex<ld>(1,0);
    roots[3][1]=complex<ld>(-0.93969,-0.34202);
    roots[3][2]=complex<ld>(-0.93969,0.34202);
    roots[3][3]=complex<ld>(0.76604,0.64279);
    roots[3][4]=complex<ld>(0.76604,-0.64279);
    roots[3][5]=complex<ld>(-0.5,0.86603);
    roots[3][6]=complex<ld>(-0.5,-0.86603);
    roots[3][7]=complex<ld>(0.17365,0.98481);
    roots[3][8]=complex<ld>(0.17365,-0.98481);
    roots[4][0]=complex<ld>(-0.95106,-0.30902);
    roots[4][1]=complex<ld>(0.95106,0.30902);
    roots[4][2]=complex<ld>(0.95106,-0.30902);
    roots[4][3]=complex<ld>(-0.95106,0.30902);
    roots[4][4]=complex<ld>(-0.58779,-0.80902);
    roots[4][5]=complex<ld>(0.58779,-0.80902);
    roots[4][6]=complex<ld>(0.58779,0.80902);
    roots[4][7]=complex<ld>(-0.58779,0.80902);
    choice_2_size[0]=1;
    choice_2_size[1]=3;
    choice_2_size[2]=5;
    choice_2_size[3]=9;
    choice_2_size[4]=8;
    root_2_color[0]=9;
    root_2_color[1]=5;
    root_2_color[2]=11;
    root_2_color[3]=1;
    root_2_color[4]=2;
    root_2_color[5]=0;
    root_2_color[6]=15;
    root_2_color[7]=14;
    root_2_color[8]=13;

    int myc;
    myc=0; rgb2root[myc][0] = 200; rgb2root[myc][1] =   0; rgb2root[myc][2] =   0;
    myc=1; rgb2root[myc][0] =   0; rgb2root[myc][1] = 200; rgb2root[myc][2] =   0;
    myc=2; rgb2root[myc][0] =   0; rgb2root[myc][1] =   0; rgb2root[myc][2] = 200;
    myc=3; rgb2root[myc][0] = 200; rgb2root[myc][1] = 200; rgb2root[myc][2] = 200;
    myc=4; rgb2root[myc][0] = 100; rgb2root[myc][1] = 200; rgb2root[myc][2] = 200;
    myc=5; rgb2root[myc][0] = 200; rgb2root[myc][1] = 100; rgb2root[myc][2] = 200;

    ll steps,choice;
    ld zoom;
    cout<<"Select an example from 1 to 5: ";
    cin>>choice;
    while(choice>5 or choice<1){
        cout<<"Please select an example from 1 to 5: ";
        cin>>choice;
    }
    cout<<"Select the number of iterations: ";
    cin>>steps;
    cout<<"Select the zoom level must be above 0: ";
    cin>>zoom;
    while(zoom==0){
        cout<<"Please select non 0 zoom level: ";
        cin>>zoom;
    }


    choice--;
    // calc max_roots_distance
    for(ll i=1; i<choice_2_size[choice]; i++){
        max_root_distance+=sqrt(pow((real(roots[choice][0])-real(roots[choice][i])),2)+pow((imag(roots[choice][0])-imag(roots[choice][i])),2));
    }


    initgraph(&gdriver, &gmode, "d://tc//bgi");
    point mid_point;
    mid_point.x=Sizex/2;
    mid_point.i=Sizey/2;
    for(ll i=0;i<=Sizex;i++){
        for(ll j=0;j<=Sizey;j++){
            complex<ld> curr_p((i-mid_point.x)/zoom,(j-mid_point.i)/zoom);
            for(ll k=0;k<steps;k++){
                curr_p=curr_p-calc_transition(curr_p,choice);
            }
            pair<ll,ld> id=calc_closest(curr_p,roots[choice],choice_2_size[choice]);
            draw_pretty_pixel(i,j,id.first,id.second);
            //putpixel(i,j,root_2_color[id]);
        }
    }
    getch();
    closegraph();
    return 0;
}

void draw_pretty_pixel(ll x,ll y,ll col1, ld percentage){
    int r,g,b;
    r=int(rgb2root[col1][0]);
    g=int(rgb2root[col1][1]);
    b=int(rgb2root[col1][2]);
    putpixel(x,y,col1+2);
    //putpixel(x,y,COLOR(r,g,b));
    //COLOR(i%256,j%256,(i+j)%256)
}




