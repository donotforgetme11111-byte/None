#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int n,m,K=5;int *cl;int *occ,*occs,*occn;char *a;int *ntrue,*fal,*wf,nf;
unsigned long long s=88172645463325252ULL;static inline unsigned long long rnd(){s^=s<<13;s^=s>>7;s^=s<<17;return s;}
int main(int argc,char**argv){char buf[64];if(argc>2)s^=atoll(argv[2]);FILE*f=fopen(argv[1],"r");fscanf(f,"%s %s %d %d",buf,buf,&n,&m);
cl=malloc(sizeof(int)*m*K);int*cnt=calloc(n+1,sizeof(int));int*cntn=calloc(n+1,sizeof(int));
for(int i=0;i<m;i++){for(int j=0;j<K;j++){fscanf(f,"%d",&cl[i*K+j]);}int z;fscanf(f,"%d",&z);}
// occurrence lists by var (both signs)
occs=calloc(n+2,sizeof(int));for(int i=0;i<m*K;i++)occs[abs(cl[i])+1]++;for(int v=1;v<=n+1;v++)occs[v]+=occs[v-1];
occ=malloc(sizeof(int)*m*K);int*pos=calloc(n+1,sizeof(int));for(int i=0;i<m*K;i++){int v=abs(cl[i]);occ[occs[v]+pos[v]++]=i;}
a=malloc(n+1);ntrue=calloc(m,sizeof(int));fal=malloc(sizeof(int)*m);wf=malloc(sizeof(int)*m);
double cb=argc>4?atof(argv[4]):3.7,eps=1.0;double pr[64];for(int i=0;i<64;i++)pr[i]=pow(eps+i,-cb);
for(int v=1;v<=n;v++)a[v]=rnd()&1;nf=0;
for(int i=0;i<m;i++){int t=0;for(int j=0;j<K;j++){int l=cl[i*K+j];if((l>0)==a[abs(l)])t++;}ntrue[i]=t;if(!t){wf[i]=nf;fal[nf++]=i;}}
long long flips=0;int best=1<<30;clock_t st=clock();
while(nf){int c=fal[rnd()%nf];double p[5],sum=0;
 for(int j=0;j<K;j++){int v=abs(cl[c*K+j]);int br=0;for(int o=occs[v];o<occs[v+1];o++){int li=occ[o];int ci=li/K;int l=cl[li];if(ntrue[ci]==1&&((l>0)==a[v]))br++;}p[j]=pr[br<64?br:63];sum+=p[j];}
 double r=(rnd()%1000000)/1e6*sum;int j=0;while(j<4&&r>p[j]){r-=p[j];j++;}
 int v=abs(cl[c*K+j]);a[v]^=1;flips++;
 for(int o=occs[v];o<occs[v+1];o++){int li=occ[o];int ci=li/K;int l=cl[li];if((l>0)==a[v]){if(ntrue[ci]++==0){int w=wf[ci];fal[w]=fal[--nf];wf[fal[w]]=w;}}else{if(--ntrue[ci]==0){wf[ci]=nf;fal[nf++]=ci;}}}
 if(nf<best)best=nf;
 if((flips&0xFFFFF)==0&&(double)(clock()-st)/CLOCKS_PER_SEC>atof(argc>3?argv[3]:"600")){fprintf(stderr,"timeout best %d flips %lld\n",best,flips);return 1;}
}
fprintf(stderr,"flips %lld time %.2f\n",flips,(double)(clock()-st)/CLOCKS_PER_SEC);
for(int v=1;v<=n;v++)putchar(a[v]?'1':'0');putchar('\n');return 0;}
