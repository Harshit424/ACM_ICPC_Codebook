// /home/vivek/.config/sublime-text-3/Packages/User/CF/dist/Codechef/COON2019/sample.cpp
struct node
{
   node *left, *right;
   node(node *left=NULL, node *right=NULL):
      left(left), right(right){}
};
node *null = new node();
node *tree[N];
node *insert(node *p, int key, int radix = 30){
   if(!p)p = null;
   if(radix < 0)return null;
   if(key & (1<<radix)){
      return new node(p->left, insert(p->right, key, radix-1));
   }
   else{
      return new node(insert(p->left, key, radix-1), p->right);
   }
}
int getMin(node *p, int key, int radix = 30){
   if(!p)p = null;
   if(radix < 0)return 0;
   if(key & (1<<radix)){
      if(p->right){
         return getMin(p->right, key, radix-1);
      }
      else{
         return (1<<radix)|getMin(p->left, key, radix-1);
      }
   }
   else{
      if(p->left){
         return getMin(p->left, key, radix-1);
      }
      else{
         return (1<<radix) | getMin(p->right, key, radix-1);
      }
   }   
}
int getMax(node *p, int key, int radix = 30){
   if(!p)p = null;
   if(radix < 0)return 0;
   if(key & (1<<radix)){
      if(p->left){
         return (1<<radix)|getMax(p->left, key, radix-1);
      }
      else{
         return getMax(p->right, key, radix-1);
      }
   }
   else{
      if(p->right){
         return (1<<radix) | getMax(p->right, key, radix-1);
      }
      else{
         return getMax(p->left, key, radix-1);
      }
   }   
}
void deallocate(node *root){ 
   if(!root)
      return ;
   deallocate(root->L);
   deallocate(root->R);
   delete root;
}
/******
USAGE
tree[node] = insert(tree[parent], key_into_consideration);
Ex :- tree[v] = insert(tree[u], key[v]);
Some common mistakes :-
insert(node *p, int key, int radix = ****30*****, check this default value twice...)
deallocate tree after usage
******/
/*
Example Problem :- https://www.codechef.com/MAY17/problems/GPD
*/
