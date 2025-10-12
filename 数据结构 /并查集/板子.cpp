
int fid[N];
int root(int x){
    if(x!=fid[x]) fid[x]=root(fid[x]);
    return fid[x];
}

void merge(int x,int y){
    x=root(x);y=root(y);
    if(x!=y) fid[x] = y ;
}

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)fid[i]=i;
    while (m--)
    {
        int x,y;cin>>x>>y;
        merge(x,y);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(root(i)==i)ans++;
    }
    cout<<ans<<endl;
    
}
