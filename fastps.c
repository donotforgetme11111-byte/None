#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define K 5
int n,m,*cl,*os,*oc,*nt,*cv,*br,*fal,*wf,nf;char*a;
unsigned long long s=88172645463325252ULL;static inline unsigned long long rnd(){s^=s<<13;s^=s>>7;s^=s<<17;return s;}
int main(int argc,char**argv){char b[64];if(argc>2)s^=atoll(argv[2])*2654435761ULL;double lim=argc>3?atof(argv[3]):600,cb=argc>4?atof(argv[4]):3.7;
FILE*f=fopen(argv[1],"r");if(fscanf(f,"%s %s %d %d",b,b,&n,&m)!=4)return 2;cl=malloc(4*m*K);
for(int i=0;i<m;i++){for(int j=0;j<K;j++)if(fscanf(f,"%d",&cl[i*K+j])!=1)return 2;int z;if(fscanf(f,"%d",&z)!=1)return 2;}
os=calloc(n+2,4);for(int i=0;i<m*K;i++)os[abs(cl[i])+1]++;for(int v=1;v<=n+1;v++)os[v]+=os[v-1];
oc=malloc(4*m*K);int*p=calloc(n+1,4);for(int i=0;i<m*K;i++){int v=abs(cl[i]);oc[os[v]+p[v]++]=i;}
a=malloc(n+1);nt=calloc(m,4);cv=calloc(m,4);br=calloc(n+1,4);fal=malloc(4*m);wf=malloc(4*m);
double pr[256];for(int i=0;i<256;i++)pr[i]=pow(1.0+i,-cb);
if(argc>5){FILE*g=fopen(argv[5],"r");for(int v=1;v<=n;v++){int c=fgetc(g);a[v]=(c=='1');}fclose(g);}else for(int v=1;v<=n;v++)a[v]=rnd()&1;
nf=0;for(int i=0;i<m;i++){int t=0,x=0;for(int j=0;j<K;j++){int l=cl[i*K+j];if((l>0)==a[abs(l)]){t++;x^=abs(l);}}nt[i]=t;cv[i]=x;if(t==1)br[x]++;if(!t){wf[i]=nf;fal[nf++]=i;}}
long long fl=0;int best=1<<30;clock_t st=clock();
while(nf){int c=fal[rnd()%nf];double pp[K],sum=0;for(int j=0;j<K;j++){int v=abs(cl[c*K+j]);int x=br[v];pp[j]=pr[x<256?x:255];sum+=pp[j];}
 double r=(double)(rnd()>>11)/9007199254740992.0*sum;int j=0;while(j<K-1&&r>pp[j]){r-=pp[j];j++;}
 int v=abs(cl[c*K+j]);a[v]^=1;fl++;
 for(int o=os[v];o<os[v+1];o++){int li=oc[o],ci=li/K,l=cl[li];
  if((l>0)==a[v]){ // became true literal
   int t=nt[ci]++;if(t==0){br[v]++;int w=wf[ci];fal[w]=fal[--nf];wf[fal[w]]=w;}else if(t==1){br[cv[ci]]--;br[v]+=0;}
   cv[ci]^=v;
  }else{int t=--nt[ci];cv[ci]^=v;if(t==0){br[v]--;wf[ci]=nf;fal[nf++]=ci;}else if(t==1){br[cv[ci]]++;}}
 }
 if(nf<best)best=nf;
 if((fl&0xFFFFF)==0&&(double)(clock()-st)/CLOCKS_PER_SEC>lim){fprintf(stderr,"timeout best %d flips %lld\n",best,fl);return 1;}
}
fprintf(stderr,"SOLVED flips %lld time %.1f\n",fl,(double)(clock()-st)/CLOCKS_PER_SEC);for(int v=1;v<=n;v++)putchar(a[v]?'1':'0');putchar('\n');return 0;}
