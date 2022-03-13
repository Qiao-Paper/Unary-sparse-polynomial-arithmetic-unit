#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 10    //The number of polynomial 
typedef struct LNode{
	float coef;
	int expn;
	struct LNode *next;
}LNode, *LinkList;
LinkList L[N]={NULL};
LinkList DestoryPolyn(LinkList pl1);

LinkList CreatePolyn(LinkList pl1){  //Create polynomial 
	DestoryPolyn(pl1);
	float c;
	int e;
	LinkList p=NULL,p1=NULL;
    do{     //Need to consider separately when plugging in value for the first time 
    	printf("Please key in the exponent. Key in any negative value to step back.\n");
	    scanf("%d",&e);
    	if(e<0){
    		printf("Cancel\n");
		    return NULL;
	    }
	    p=pl1=(LinkList)malloc(sizeof(LNode));
	    p->expn=e;
	    printf("Please key in the coefficient. Key in 0 to step back.\n");
	    scanf("%f",&c);
	    if(c==0.0){
	    	pl1=NULL;
	    	free(p);
	    	p=NULL;
	    	printf("Cancel\n");
	    	return NULL;
		}
	    else{
	    	p->coef=c;
	        p->next=NULL;
		}
	} while(!p);
	
	printf("Please key in the exponent. Key in any negative value to step back.\n");
	scanf("%d",&e);

    while(e>=0){
    	p=(LinkList)malloc(sizeof(LNode));
    	p->expn=e;
    	printf("Please key in the coefficient. Key in 0 to step back.\n");
	    scanf("%f",&c);
	    if(c==0)  free(p);
	    else{
		    p->coef=c;
	        p->next=NULL;
	    }
	    if(p->expn<pl1->expn){  //Consider separately when the exponent is at its minimum 
	    	p->next=pl1;
	    	pl1=p;
		}
		else{
			p1=pl1;
			while(p1->next&&p->expn>p1->next->expn)  p1=p1->next;
			p->next=p1->next;
			p1->next=p;
		}
		printf("Please key in the exponent. Key in any negative value to step back.\n");
	    scanf("%d",&e);
	}
	return pl1;
}
        
void PrintPolyn(LinkList pl1){  //Print polynomial 
	if(!pl1)  printf("Polynomial does not exist.\n");
	else{
		LinkList p=pl1;
		printf("f(x)=");
	    while(p){
		    printf("(%fx^%d)",p->coef,p->expn);
		    p=p->next;
		    if(p)  printf("+");
	    }
	}
}

LinkList DestoryPolyn(LinkList pl1){  //Destroy polynomial 
	if(!pl1)  return NULL;
	LinkList p1=pl1,p2=p1->next;
	pl1=NULL;
	while(p2){
		free(p1);
		p1=p2;
		p2=p2->next;
	}
	free(p1);
	return NULL; 
} 

LinkList CopyPolyn(LinkList pl1, LinkList pl2){  //Replicate polynomial 
	LinkList p1=pl1,p2=NULL;
	pl2=DestoryPolyn(pl2);  //Distroy and replicate 
	if(!pl1){
		printf("Polynomial does not exist.\n");
	    return pl2;
	}
	p2=pl2=(LinkList)malloc(sizeof(LNode));
	*pl2=*p1;
	pl2->next=NULL;
	p1=p1->next;
	while(p1){
		p2->next=(LinkList)malloc(sizeof(LNode));
		p2=p2->next;
		*p2=*p1;
		p2->next=NULL;
		p1=p1->next;
	}
	return pl2;
}

LinkList CopyPolyn2(LinkList pl1, LinkList pl2){  //Replicate the polynomial with coefficient of same magnitude but different sign
	LinkList p1=pl1,p2=NULL;
	pl2=DestoryPolyn(pl2);  //Distroy and replicate 
	if(!pl1){
		printf("Polynomial does not exist\n");
	    return pl2;
	}
	p2=pl2=(LinkList)malloc(sizeof(LNode));
	p2->coef=(-p1->coef);
	p2->expn=p1->expn;
	p2->next=NULL;
	p1=p1->next;
	while(p1){
		p2->next=(LinkList)malloc(sizeof(LNode));
		p2=p2->next;
		p2->coef=(-p1->coef);
	    p2->expn=p1->expn;
		p2->next=NULL;
		p1=p1->next;
	}
	return pl2;
}

LinkList PlusPolyn(LinkList pl1, LinkList pl2){  //Summation of polynomials 
	LinkList A=NULL;  //Create a new pointer to store the summational polynomial 
	LinkList p1=pl1, p2=pl2, p=NULL, p3=NULL;
	if((!p1)&&p2)  A=CopyPolyn(p2, A);
	else{
	    if((!p2)&&p1)  A=CopyPolyn(p1, A);
	    else{
	        while(p1&&p2){
	        	if(p1->expn<p2->expn){
	        		p3=(LinkList)malloc(sizeof(LNode));
	        		if(!p)  p=p3;
	        		else{
	        			p->next=p3;
	        			p=p->next;
					}
	        		*p3=*p1;
	        		p3->next=NULL;
	        		p1=p1->next;
	        		if(A==NULL)  A=p;//execute when first plugging in 
				}
				else{
				    if(p1->expn>p2->expn){
	        		    p3=(LinkList)malloc(sizeof(LNode));
	        		    if(!p)  p=p3;
	        		    else{
	        			    p->next=p3;
	        			    p=p->next;
					    }
	        		    *p3=*p2;
	        		    p3->next=NULL;
	        		    p2=p2->next;
	        		    if(A==NULL)  A=p;//execute when first plugging in 
				    }
				    else{
				        if(p1->expn==p2->expn){
					        if(p1->coef+p2->coef==0); 
	        		        else{
	        			        p3=(LinkList)malloc(sizeof(LNode));
	        			        if(!p)  p=p3;
	        		            else{
	        			            p->next=p3;
	        			            p=p->next;
					            }
	        		            p3->expn=p1->expn;
	        		            p3->coef=p1->coef+p2->coef;
	        		            p3->next=NULL;
	        		            if(A==NULL)  A=p;//execute when first plugging in 
					        }
					        p1=p1->next;
				            p2=p2->next;
				        }
			        }
			    }
			}
			if(p1)  p->next=CopyPolyn(p1, p->next);
			if(p2)  p->next=CopyPolyn(p2, p->next);
	    }
	}
	PrintPolyn(A);
	return A;
}

LinkList MinusPolyn(LinkList pl1, LinkList pl2){  //Subtraction of polynomials 
	LinkList A=NULL;  //Create a new pointer to store the subtraction of polynomials.
	LinkList p1=pl1, p2=pl2, p=NULL, p3=NULL;
	
	    if((!p2)&&p1)  A=CopyPolyn(p1, A);  //If polynomial 1 exsit but polynomial 2 does not exsit, replicate directly 
	    else{
	        while(p1&&p2){
	        	if(p1->expn<p2->expn){
	        		p3=(LinkList)malloc(sizeof(LNode));
	        		if(!p)  p=p3;
	        		else{
	        			p->next=p3;
	        			p=p->next;
					}
	        		*p3=*p1;
	        		p3->next=NULL;
	        		p1=p1->next;
	        		if(A==NULL)  A=p;//execute when first plugging in 
				}
				else{
				    if(p1->expn>p2->expn){
	        		    p3=(LinkList)malloc(sizeof(LNode));
	        		    if(!p)  p=p3;
	        		    else{
	        			    p->next=p3;
	        			    p=p->next;
					    }
	        		    *p3=*p2;
	        		    p3->next=NULL;
	        		    p2=p2->next;
	        		    if(A==NULL)  A=p;//execute when first plugging in 
				    }
				    else{
				        if(p1->expn==p2->expn){
					        if(p1->coef-p2->coef==0); 
	        		        else{
	        			        p3=(LinkList)malloc(sizeof(LNode));
	        			        if(!p)  p=p3;
	        		            else{
	        			            p->next=p3;
	        			            p=p->next;
					            }
	        		            p3->expn=p1->expn;
	        		            p3->coef=p1->coef-p2->coef;
	        		            p3->next=NULL;
	        		            if(A==NULL)  A=p;//execute when first plugging in 
					        }
					        p1=p1->next;
				            p2=p2->next;
				        }
			        }
			    }
			}
			if(p1)  p->next=CopyPolyn(p1, p->next);
			if(p2)  p->next=CopyPolyn2(p2, p->next);  //Fill up the term at the end 
	    }	
	PrintPolyn(A);
	return A;
}

LinkList ProductPolyn(LinkList pl1, LinkList pl2){  //Product of polynomials 
	LinkList A=NULL;  //Create a new pointer to store the product of polynomials
	LinkList p1=NULL, p=NULL, q=NULL, q2=NULL, p5=pl1, p6=pl2;
	if((!pl1)||(!pl2)){
	    printf("Error.\n");
	    return NULL;
	}
	int e;
	float c;
	A=(LinkList)malloc(sizeof(LNode));
	A->expn=p5->expn+p6->expn;
	A->coef=p5->coef*p6->coef;
	A->next=NULL;
	p5=p5->next;  //Insert the first element separately at first 
	while(p6){  //Multiply 
		while(p5){
    	    p=(LinkList)malloc(sizeof(LNode));
    	    p->expn=p5->expn+p6->expn;
  		    p->coef=p5->coef*p6->coef;
	        p->next=NULL;
	        p1=A;
	        while(p1->next&&p->expn>p1->next->expn)  p1=p1->next;
	        if(p1->next&&(p->expn==p1->next->expn)){
	        	p1->next->coef+=p->coef;
	        	free(p);
	        	p=NULL;
			}
	        else{
	        	p->next=p1->next;
	        	p1->next=p;
			}
			p5=p5->next;
		}
		p6=p6->next; 
		p5=pl1;
	}
	
	//Delete the element with coefficient 0 
	while((A->coef==0)&&A!=NULL){
		q=A;
		A=A->next;
		free(q);
		q=NULL;
	}
	for(q=A; q!=NULL; q=q->next){
		if(q->next&&q->next->coef==0){
			q2=q->next;
			q->next=q->next->next;
			free(q2);
			q2=NULL;
		}
	} 
	return A;
}



LinkList DerivationPolyn(LinkList pl1){  //Find the derivative 
	LinkList A=NULL;  //Create a new pointer to store the derivative of polynomials
	LinkList p=NULL,p1=pl1;
	if(p1==NULL){
	    printf("Polynomial does not exist.\n");
	    return NULL;
	}
	if(p1->expn==0&&p1->next==NULL)  return NULL;
    while(p1){
	    if(p1->expn==0);
	    else{
	    	if(p==NULL){
	    		p=(LinkList)malloc(sizeof(LNode));
	    	    p->coef=p1->coef*p1->expn;
	            p->expn=p1->expn-1;
	            p->next=NULL;
			}
	    	else{
	    		p->next=(LinkList)malloc(sizeof(LNode));
	    		p=p->next;
	    	    p->coef=p1->coef*p1->expn;
	            p->expn=p1->expn-1;
	            p->next=NULL;
	        }	
		}
	    p1=p1->next;
	    if(A==NULL)  A=p;
	}
	return A;
}

float EvaluationPolyn(LinkList pl1,float a){  //Evaluate 
	float S=0;
	LinkList p=pl1;
	if(!p){
	    printf("Polynomial does not exist.\n");
		return 0;
	}
	while(p){
		S+=p->coef*pow(a, p->expn);
		p=p->next;
	}
	return S;
}

LinkList Indefinite_Integral_Polyn(LinkList pl1,LinkList A){  //Indefinite integral 
	LinkList p=NULL,p1=pl1;
	if(p1==NULL){
	    printf("Polynomial does not exist.\n");
	    return NULL;
	}
    while(p1){
	    if(p1->expn==0);
	    else{
	    	if(p){
	    		p->next=(LinkList)malloc(sizeof(LNode));
	    		p=p->next;
			}
			else  p=(LinkList)malloc(sizeof(LNode));
			p->next=NULL;
	    	p->coef=p1->coef/(p1->expn+1);
	        p->expn=p1->expn+1;
		}
	    p1=p1->next;
	    if(A==NULL)  A=p;
	}
	return A;
}



float Definite_Integral_Polyn(LinkList pl1,float a,float b){  //Definite integral 
	LinkList A=NULL;
	A=Indefinite_Integral_Polyn(pl1,A);
	float M;
	M=EvaluationPolyn(A,b)-EvaluationPolyn(A,a);
	return M;
}

void Save(LinkList o){
	printf("\Whether n stores the resultant polynomial? If yes, key in the subscript of the position where it is stored, otherwise, key in  -1\n");
	int k; 
	scanf("%d",&k);
	if(k>=0&&k<N){
		L[k]=DestoryPolyn(L[k]);
		L[k]=CopyPolyn(o, L[k]);
	}
	printf("\n");
}

void main(){
	int menu,i,j,k;
    float a,b; 
    LinkList o=NULL;
	while(1){
		printf("0--End\n1--Create polynomial\n2--Display polynomial\n3--Destroy polynomial\n4--Clear polynomial\n5--Replicate polynomial\n6--Summation of two sparse polynomials\n7--Subtraction of two sparse polynomials\n8--Product of two sparse polynomials\n9--Find the n-th derivative of the sparse polynomial\n10--Evaluate the sparse polynomial at x=a\n11--Evaluate the definite integral of the sparse polynomial in the region [a,b]\n12--n-th exponent of the sparse polynomial\n");
		printf("Please choose the menu:\n");
		scanf("%d",&menu);
		switch(menu){
			case 0:return;
			case 1:
			    printf("Please key in the subscript of the position where the new polynomial is created.\n");
			    scanf("%d",&i);
				L[i]=CreatePolyn(L[i]);
				printf("\n");
				break;
			case 2:
			    printf("Please key in the subscript of the position where the polynomial to be displayed is stored.\n");
			    scanf("%d",&i);
				PrintPolyn(L[i]);
				printf("\n");
				break;
			case 3:
			    printf("Please key in the subscript of the position where the polynomial to be destroyed is stored.\n");
			    scanf("%d",&i);
				L[i]=DestoryPolyn(L[i]);
				printf("\n");
				break;
			case 4:
			    printf("Sure to clear all the polynomials? Key in 1 to continue.\n");
				scanf("%d",i); 
				if(i==1){
					for(j=0; j<N; j++)  L[j]=DestoryPolyn(L[j]);
				}
				printf("\n");
				break;	
			case 5:
			    printf("Please key in the subscript of the position where the polynomial replicated is stored, and the subscript of the position after replication.\n");
			    scanf("%d %d",&i,&j);
				L[j]=CopyPolyn(L[i],L[j]);
				printf("\n");
				break;
			case 6:
			    printf("Please key in the subscript of the position where the two polynomials whose summation is wanted are stored.\n");
			    scanf("%d %d",&i,&j);
				o=PlusPolyn(L[i],L[j]);
				
	            Save(o);
	            o=DestoryPolyn(o);
				break;
			case 7:
			    printf("Please key in the subscript of the position where the two polynomials whose subtraction is wanted are stored.\n");
			    scanf("%d %d",&i,&j);
			    o=MinusPolyn(L[i],L[j]);
			    
				Save(o);
	            o=DestoryPolyn(o);
				break;
			case 8:
			    printf("Please key in the subscript of the position where the two polynomials whose product is wanted are stored.\n");
			    scanf("%d %d",&i,&j);
				o=ProductPolyn(L[i],L[j]);
				
				Save(o);
	            o=DestoryPolyn(o);
				break;
			case 9:
			    printf("Please key in the subscript of the position where the polynomial whose derivative is wanted is stored.\n");
			    scanf("%d %d",&i,&j);
			    if(j==1)  o=DerivationPolyn(L[i]);
				if(j>=2){
					o=DerivationPolyn(L[i]);
					for(k=2;k<=j;k++)  o=DerivationPolyn(o);
				}
				Save(o);
	            o=DestoryPolyn(o);
				break;
			case 10:
			    printf("Please key in the subscripts of the positions where the polynomial to be evaluated and its value are stored.\n");
			    scanf("%d %f",&i,&a);
				printf("%f",EvaluationPolyn(L[i],a));
				printf("\n");
				break;	
			case 11:
			    printf("Please key in the subscript of the position where the polynomial whose integral is wanted is stored and integrating range.\n");
			    scanf("%d %f %f",&i,&a,&b);
				printf("%f",Definite_Integral_Polyn(L[i],a,b));
				printf("\n");
				break;	
			case 12:
				printf("Please key in the subscript of the position where the polynomial whose exponential value is wanted is stored and its exponent.\n");
				scanf("%d %d",&i,&j);
				if(j<=0){
				     printf("error\n");
				     break;
				}
				o=L[i];
				for(k=2; k<=j; k++){
					o=ProductPolyn(L[i],o);
				}
				Save(o);
	            o=DestoryPolyn(o);
	            break;
			
			default:printf("Error.\n");
		}//end switch
	}//end while
}//end main
