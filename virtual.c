#include<stdio.h>
#include<string.h>

int compPR(int, int, int*);
void start(int, int, int*);

int main(int argc, char *argv[])
{

FILE * inFile;

int Page, Frame, pageReq, compReturn, indVal, lruPage, optPage;
						
char fName[50], Algorithm[50];  

int fNUM = 0, pageFaults = 0;




	sscanf(argv[1],"%s", fName);				// arg File Name
	sscanf(argv[2],"%s", Algorithm);			// arg Algorithm
  
	inFile = fopen(fName,"r");				// Filename based on args
	fscanf(inFile,"%d%d%d",&Page,&Frame,&pageReq); 
	
	printf(" %d %d %d \n", Page,Frame,pageReq);		// Parse file for page / frame / Page Requests

	int nextReq[pageReq];

	for(int i=0;i < pageReq; i++)
	{
		fscanf(inFile,"%d", &nextReq[i]);
	}
	
	fclose(inFile);



	int fillVal[Frame];
	int Index[Page + 1];

		if(strcmp(Algorithm,"FIFO") == 0)
		{

			printf("(FIFO)\n");

			start(Frame, -1, fillVal);

			for(int i = 0; i < pageReq; i++)
			{

			compReturn = compPR(nextReq[i], Frame, fillVal);

				if(compReturn != -1) 
				{
				printf("Page %d already in Frame %d \n", nextReq[i], compReturn);
				}

				else if(fillVal[fNUM] == -1) 
				{

				fillVal[fNUM] = nextReq[i];
				printf("Page %d loaded into Frame %d \n", nextReq[i], fNUM);
			
				fNUM = (fNUM + 1) % Frame;
				/*fNUM++;

					if(fNUM == 4)
					{
					fNUM = 0;
					}
				*/
				pageFaults++;
	  
				}

				else 
				{
				 
				  
				printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n",
										fillVal[fNUM], fNUM, nextReq[i], fNUM );
				fillVal[fNUM] = nextReq[i];
				//fNUM++;

				fNUM = (fNUM + 1) % Frame;
					/*if(fNUM == 4)
					{
					fNUM = 0;
					}*/


				pageFaults++;

				}
			}

		printf("%d Page Faults \n", pageFaults);

		}


		if(strcmp(Algorithm,"LRU") == 0)
		{

		printf("(LRU)\n");
		start(Frame, -1, fillVal);

			for(int i=0; i < pageReq; i++)
			{

			compReturn = compPR(nextReq[i], Frame, fillVal); 

				if(compReturn != -1)
				{
					printf("Page %d already in Frame %d \n", nextReq[i], compReturn);
					Index[nextReq[i]] = i;
				}
				else if(fillVal[fNUM] == -1) 
				{

					fillVal[fNUM] = nextReq[i];
					printf("Page %d loaded into Frame %d \n", nextReq[i], fNUM);
					fNUM++;

						if(fNUM == 4)				// Reset Frame to 0
						{
						fNUM = 0;
						}

					Index[nextReq[i]] = i;

					pageFaults++;
			  
				}

				else 
				{
				lruPage = 0;
				indVal = Index[fillVal[0]];
				

					for(int k = 1; k < Frame; k++) 
					{
						if(indVal > Index[fillVal[k]])
						{

						lruPage = k;
						indVal = Index[fillVal[k]];

						}
					}

				printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n", 
										fillVal[lruPage], lruPage, nextReq[i], lruPage);
				fillVal[lruPage] = nextReq[i];
				Index[nextReq[i]] = i;

				pageFaults++;

				}
			}


		printf("%d Page Faults \n", pageFaults);

		}


		if(strcmp(Algorithm,"OPT") == 0)
		{

			start(Frame, -1, fillVal);
			printf("(OPT)\n");

			for(int i = 0; i < pageReq; i++)
			{

			compReturn = compPR(nextReq[i], Frame, fillVal); 

				if(compReturn != -1)
				{
				printf("page %d already in Frame %d \n", nextReq[i], compReturn);
				}

				else if(fillVal[fNUM] == -1) 
				{
				fillVal[fNUM] = nextReq[i];
				printf("page %d loaded into Frame %d \n", nextReq[i], fNUM);

				fNUM++;

					if(fNUM == 4)
					{
					fNUM = 0;
					}

				pageFaults++;
				  
				}

				else 
				{
				  
				start(Page + 1, pageReq + 2, Index);	// ??


					for(int n = 0; n < Frame; n++) 
					{

						for(int m = i + 1; m < pageReq; m++)
						{
							if(fillVal[n] == nextReq[m])
							{

							Index[nextReq[m]] = m;
							break;
							}

						}
					}

					optPage = 0;
					indVal = Index[fillVal[0]];


					for(int j = 1; j < Frame; j++) 
					{
						if(indVal < Index[fillVal[j]])
						{
							optPage = j;
							indVal = Index[fillVal[j]];
						}
					}

						printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n",
											fillVal[optPage], optPage, nextReq[i], optPage);

					
						fillVal[optPage] = nextReq[i];

						pageFaults++;

				}
			}

		printf("%d Page Faults\n", pageFaults);

		}

}


int compPR(int next, int f,int fillVal[]) 			// check val against initial and new filled values 
{
	for(int i = 0; i < f; i++)
	{
		if(next == fillVal[i])
		//printf("check: %d \n", frame[i]);
		return i;
	}

return -1;

}

void start(int f, int fill, int Frame[]) 
{
	for(int j = 0; j < f; j++)
	Frame[j] = fill;
	//count++;
	//printf("initial: %d \n", count);
}
