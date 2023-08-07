// Binary Search Tree operations in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
    int key;
    struct node *left, *right;
    int numcars;
    int cars[512];
};

struct nodesmall {
    int key;
    int maxcar;
    int label;
};

int distanza;
int automobile;
int inserito = 0;
struct node* appoggio=NULL;
int cancellato = 0;
int totalestazioni = 0;

struct node* search(struct node *root, int x)
{
    if(root==NULL || root->key==x) //if root->data is x then the element is found
        return root;
    else if(x>root->key) // x is greater, so we will search the right subtree
        return search(root->right, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left,x);
}

void insertAUTO(int *cars,int autonomia,int numcars)
{
    int i = numcars-1;
    while (i >= 0 && cars[i] > autonomia) {
        cars[i+1] = cars[i];
        i--;
    }
    // Insert the element in its correct position
    cars[i + 1] = autonomia;
}

// Create a node
struct node *newNode(int item,char * input) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->numcars = 0;
    inserito = 1;
    appoggio = temp;
    return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
    if (root != NULL) {
        // Traverse left
        inorder(root->left);

        // Traverse root
        printf("%d -> (%d) ", root->key,root->numcars);

        for (int i=0;i<root->numcars;i++)
            printf("%d ",root->cars[i]);
        printf("\n");

        // Traverse right
        inorder(root->right);
    }
}

// Insert a node
struct node *insert(struct node *node, int key,char* linea) {
    // Return a new node if the tree is empty
    if (node == NULL) return newNode(key,linea);

    if (key == node->key)
    {
        return node;
    }

    // Traverse to the right place and insert the node
    if (key < node->key)
        node->left = insert(node->left, key,linea);
    else
        node->right = insert(node->right, key,linea);

    return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
    struct node *current = node;

    // Find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
    // Return if the tree is empty
    if (root == NULL) return root;

    // Find the node to be deleted
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // If the node is with only one child or no child
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            cancellato = 1;
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            cancellato = 1;
            return temp;
        }

        // If the node has two children
        struct node *temp = minValueNode(root->right);

        // Place the inorder successor in position of the node to be deleted
        root->key = temp->key;
        // ECCO L'ERRORE, DEVO COPIARE TUTTO
        root->numcars = temp->numcars;
        for (int i=0;i<temp->numcars;i++)
            root->cars[i] = temp->cars[i];


        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

char* ottieni_distanza(char* input)
{
    distanza = 0;
    char delimiter[] = " ";
    char* token, *context;
    /* get the first token */
    token = strtok_r (input, delimiter, &context);
    token = strtok_r (NULL, delimiter, &context);
    distanza = atoi(token);
    return(context);
}

void ottieni_auto(char* input)
{
    automobile = 0;
    //memset(automobile,0,strlen(automobile));
    char delimiter[] = " ";
    char* token, *context;
    token = strtok_r (input, delimiter, &context);
    automobile = atoi(token);
}

int binarySearchAuto(int *cars, int left, int right, int element) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (cars[mid] == element)
            return mid;

        if (cars[mid] < element)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int deleteAUTO(int *cars,int autonomia,int numcars)
{
    //int returnvalue = 0;
    int pos = binarySearchAuto(cars,0,numcars-1,autonomia);
    if (pos != -1)
    {
        // trovato, lo cancello
        // Shift elements to the left to overwrite the element to be removed
        for (int i = pos; i < numcars - 1; i++) {
            cars[i] = cars[i + 1];
        }
        printf("rottamata\n");
        return (1);
    }
    else
    {
        printf("non rottamata\n");
        return (0);
    }

}

void inOrder(struct node* root, struct nodesmall* stazioni)
{
    struct node *current, *pre;
 
    if (root == NULL)
        return;
 
    current = root;
    int i = 0;
    while (current != NULL) {
 
        if (current->left == NULL) {
            //cout << current->data << " ";
            stazioni[i].key = current->key;
            if(current->numcars == 0){
                stazioni[i].maxcar = 0;
            } else 
                stazioni[i].maxcar = current->cars[current->numcars-1];
            //stazioni[i].maxcar = current->cars[current->numcars-1];
            i++;
            current = current->right;
        }
        else {
 
            // Find the inorder predecessor of current
            pre = current->left;
            while (pre->right != NULL
                   && pre->right != current)
                pre = pre->right;
 
            // Make current as the right child of its
            // inorder predecessor
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
 
            // Revert the changes made in the 'if' part to
            // restore the original tree i.e., fix the right
            // child of predecessor
            else {
                pre->right = NULL;
                //cout << current->data << " ";
                stazioni[i].key = current->key;
                if(current->numcars == 0){
                    stazioni[i].maxcar = 0;
                } else 
                    stazioni[i].maxcar = current->cars[current->numcars-1];
                i++;
                current = current->right;
            }
        }
    }
}

void inorderARRAY(struct node *root, struct nodesmall* stazioni,int i) {
    if (root != NULL) {
        // Traverse left
        inorderARRAY(root->left,stazioni,i);

        // Traverse root
        stazioni[i].key = root->key;
        if(root->numcars == 0){
            stazioni[i].maxcar = 0;
        } else 
            stazioni[i].maxcar = root->cars[root->numcars-1];
        stazioni[i].label = -1;
        i++;
        //printf("%d -> (%d) ", root->key,root->numcars);
        // Traverse right
        inorderARRAY(root->right,stazioni,i);
    }
}

// An iterative binary search function.
int binarySearchArr(struct nodesmall* arr, int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
 
        // Check if x is present at mid
        if (arr[m].key == x)
            return m;
 
        // If x greater, ignore left half
        if (arr[m].key < x)
            l = m + 1;
 
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
 
    // If we reach here, then element was not present
    return -1;
}

int calcolaPercorso(struct nodesmall* stazioni, int start, int end){

    int startIn = binarySearchArr(stazioni, 0, totalestazioni-1, start);
    int endIn = binarySearchArr(stazioni, 0, totalestazioni-1, end);
    //printf("%d %d %d %d\n", startIn, endIn, start, end);
    int curr, p, minLab;
    //minLab = totalestazioni; //E' il massimo valore possibile
    if(start < end){
        // ---------------->
        stazioni[endIn].label = 0;
        curr = endIn - 1;
        for(; curr >= startIn; curr--){
            minLab = totalestazioni;
            for(p = curr + 1; stazioni[curr].key + stazioni[curr].maxcar >= stazioni[p].key && p <= endIn; p++){
                //Qui dentro vuol dire che la stazione è raggiungibile da curr
                if(stazioni[p].label < minLab && stazioni[p].label != -1)
                    minLab = stazioni[p].label;
            }

            //Sono arrivato in una stazione non più accessibile
            if(minLab != totalestazioni)
                stazioni[curr].label = minLab + 1;
            else    
                stazioni[curr].label = -1;
        }

        //Se minLab è ancora a -1, vuol dire che non ho trovato nessuna stazione raggiungibile
        //Altrimenti metto la label della stazione precedente a minLab +1

        /*if(start == 26 && end == 1013){
            for(int i = startIn; i < endIn; i++){
                printf("%d(%d)[%d] ", stazioni[i].key, stazioni[i].label, stazioni[i].key + stazioni[i].maxcar);
            }
        }*/


        curr = startIn;
        if(stazioni[curr].label == -1)
            return -1;
        for(int currLab = stazioni[curr].label; stazioni[curr].key <= stazioni[endIn].key && curr < totalestazioni && currLab > 0; curr++){
            if(stazioni[curr].label == currLab){
                printf("%d ", stazioni[curr].key);
                currLab--;
            }
        }
        printf("%d", stazioni[endIn].key);
        printf("\n");
        
    } else if(start > end){
        // <----------------
        stazioni[endIn].label = 0;
        for(curr = endIn + 1; curr <= startIn; curr++){
            minLab = totalestazioni;
            for(p = curr - 1; stazioni[curr].key - stazioni[curr].maxcar <= stazioni[p].key && p >= endIn; p--){
                //Qui dentro vuol dire che la stazione è raggiungibile da curr
                if(stazioni[p].label < minLab && stazioni[p].label != -1)
                    minLab = stazioni[p].label;
            }

            //Sono arrivato in una stazione non più accessibile
            if(minLab != totalestazioni)
                stazioni[curr].label = minLab + 1;
            else    
                stazioni[curr].label = -1;
        } //Tolgo la roba delle label

        curr = startIn;
        
            /*for(; curr >= endIn; curr--){
                printf("%d(%d)[%d]\n", stazioni[curr].key, stazioni[curr].label, stazioni[curr].key - stazioni[curr].maxcar);
            }*/
        
        

        curr = startIn;
        int temp; //savedIn = 0, saved;
        //STAMPA 1: metodo reachability
        if(stazioni[curr].label == -1){
            //printf("nessun percorso\n");
            return -1;
        }

        /*for(int i = endIn-1; i <= startIn; i++){
            printf("%d (%d)\n", stazioni[i].key, stazioni[i].key - stazioni[i].maxcar);
        }*/

        int fineZone[stazioni[curr].label + 1];
        int fineZoneIn[stazioni[curr].label + 1];
        ///Metto subito quella d'inizio
        fineZone[0] = stazioni[startIn].key;
        fineZoneIn[0] = startIn;
        //Devo riempirle
        int count = 1, min, minIn;
        for(curr = startIn; curr > endIn && count < stazioni[startIn].label; curr--){
            min = stazioni[startIn].key; //Minimo raggiungibile 
            minIn = startIn;
            for(temp = fineZoneIn[count - 1] - 1; stazioni[temp].key >= stazioni[curr].key - stazioni[curr].maxcar && temp >= endIn; temp--){
                //Cicla fino a quando riesce ad arrivare
                //Ci salviamo il minimo
                if(stazioni[temp].key - stazioni[temp].maxcar <= min){ //Magari non serve l'uguale
                    min = stazioni[temp].key - stazioni[temp].maxcar;
                    minIn = temp; //Da quale stazione raggiungo il minimo
                }
            }

            //Sono nella prima stazione non raggiungibile
            fineZoneIn[count] = temp + 1;
            fineZone[count] = stazioni[temp + 1].key;
            count++;
            curr = minIn + 1;
        }

        fineZone[count] = stazioni[endIn].key;
        fineZoneIn[count] = endIn;
        fineZone[count]++;
        fineZone[count]--;
        //Stampo i limiti (funzionano bene)
        /*if(start == 924207416 && end == 46941576){
            for(int i = endIn-1; i <= startIn; i++){
            printf("%d (%d)\n", stazioni[i].key, stazioni[i].key - stazioni[i].maxcar);
        }
            for(int i = 0; i < stazioni[startIn].label + 1; i++){
                printf("%d ", fineZone[i]);
            }
            printf("\n");
        }*/
        
        /*for(int i = 0; i < stazioni[startIn].label + 1; i++){
            printf("%d ", fineZoneIn[i]);
        }
        printf("\n");*/
        //Ora la scansione dall'inizio (sappiamo che ci sono count+1 zone) //Stampiamo al contrario per ora
        int arrayContrario[stazioni[startIn].label + 1];
        int indexArrayContrario = 0;
        int currZone = stazioni[startIn].label - 1;
        //printf("%d ", stazioni[endIn].key);
        arrayContrario[indexArrayContrario] = stazioni[endIn].key;
        indexArrayContrario++;
        int lastInserted = stazioni[endIn].key;
        for(curr = fineZoneIn[currZone]; curr < startIn && currZone > 0; curr++){
            /*if(start == 924207416 && end == 46941576){
                printf("Inizio la ricerca in questo intervallo: [%d, %d)\n", fineZone[currZone], fineZone[currZone - 1]);
            }*/
            //printf("Inizio la ricerca in questo intervallo: [%d, %d)\n", fineZone[currZone], fineZone[currZone - 1]);
            for(; curr < fineZoneIn[currZone - 1];){
                if(stazioni[curr].key - stazioni[curr].maxcar <= lastInserted){
                    //Trovo la stazione che va bene
                    //printf("%d (raggiunge al massimo %d, l'ultimo inserito è %d) ", stazioni[curr].key, stazioni[curr].key - stazioni[curr].maxcar, lastInserted);
                    //printf("%d ", stazioni[curr].key);
                    arrayContrario[indexArrayContrario] = stazioni[curr].key;
                    indexArrayContrario++;
                    lastInserted = stazioni[curr].key;
                    curr = fineZoneIn[currZone - 1] - 1;
                    currZone--;
                    break;
                } else {
                    curr++;
                }
            }
        }
        //Dovrebbe mancare solo l'ultimo
        //printf("%d\n", stazioni[startIn].key);
        arrayContrario[indexArrayContrario] = stazioni[startIn].key;
        indexArrayContrario++;

    //Stampa al contrario
        for(int i = indexArrayContrario - 1; i > 0; i--){
            printf("%d ", arrayContrario[i]);
        }
        printf("%d", arrayContrario[0]);
        printf("\n");

        /*for(curr = startIn; stazioni[curr].key >= stazioni[endIn].key && curr >= 0; curr--){
            saved = 0;
            for(temp = curr - 1; stazioni[curr].key - stazioni[curr].maxcar <= stazioni[temp].key && temp >= endIn; temp--){
                //if(stazioni[temp].label == currLab){
                    //Serve che la label sia quello che cerco
                    if(saved == 0){
                        saved = 1;
                        savedIn = temp;
                    }
                    else if(stazioni[temp].key - stazioni[temp].maxcar <= stazioni[savedIn].key - stazioni[savedIn].maxcar){
                        //Controllo sulla reacheability
                        savedIn = temp;
                    }
                //}
            }
            printf("%d ", stazioni[savedIn].key);
            //currLab--;
            curr = savedIn+1; //Perchè poi decremento

        }
        printf("\n");*/


        //METODO 2: metodo label
        /*curr = startIn;
        if(stazioni[curr].label == -1)
            return -1;
        printf("%d ", stazioni[curr].key);
        for(int currLab = stazioni[curr].label-1; stazioni[curr].key >= stazioni[endIn].key && curr >= 0 && currLab > 0; curr--){
            
            saved = 0;
            for(temp = curr - 1; stazioni[curr].key - stazioni[curr].maxcar <= stazioni[temp].key && temp >= endIn; temp--){
                if(stazioni[temp].label == currLab && stazioni[temp].key - stazioni[temp].maxcar <= stazioni[curr].key){
                    //printf("%d ", stazioni[curr].key);
                    //currLab--;
                    //curr = temp+1;
                    //break;
                    if(saved == 0){
                        saved = 1;
                        savedIn = temp;
                    }
                    //Lo confronto col saved (se ci arrivo, ha label giusta ed è più lontano prendo quello)
                    else if(temp < savedIn)
                        savedIn = temp;
                }
            }
            printf("%d ", stazioni[savedIn].key);
            currLab--;
            curr = savedIn+1; //Perchè poi decremento
        }
        printf("%d", stazioni[endIn].key);
        printf("\n");
        */
        

        //return -1;
    } else {
        printf("%d\n", start);
    }
    return 0;
}


void pianificapercorso(struct node* root, char* linea)
{
    char delimiter[] = " ";
    char* token, *context;
    /* get the first token */
    token = strtok_r (linea, delimiter, &context);
    token = strtok_r (NULL, delimiter, &context);
    int sorgente = atoi(token);
    token = strtok_r (NULL, delimiter, &context);
    int destinazione = atoi(token);
    // ora cerco la sorgente
    struct node* source = search(root,sorgente);
    struct node* destination = search(root,destinazione);
    if ((source == NULL) || (destination == NULL))
        printf("nessun percorso\n");
    else
    {
       // ora faccio un array con tutte le stazioni e la maxcar
        struct nodesmall* stazioni = (struct nodesmall*) calloc(totalestazioni,sizeof(struct nodesmall));
        // attraverso tutto il grafo e riempio l'array
        //inorderARRAY(root, stazioni,0);
        inOrder(root, stazioni);
        // ora creo la matrice di adiacenza

        //DEBUG
        /*for(int i = 0; i < totalestazioni; i++){
            printf("%d ", stazioni[i].key);
        }*/
        int res = calcolaPercorso(stazioni, sorgente, destinazione); //! SEGSIG
        if(res == -1){
            printf("nessun percorso\n");
        }

        free(stazioni);
    }

}


// Driver code
int main(int argc, char* argv[]) {
    //double time_spent = 0.0;

    //clock_t begin = clock();

    struct node *root = NULL;

    //FILE* fp = fopen("C:\\Lavori\\Chicco\\cmake-build-debug\\open_95.txt", "r");
    FILE* fp = stdin;
    if (fp == NULL) {
        perror("Unable to open file!");
        exit(1);

    };

    char chunk[10000];

    while (fgets(chunk, sizeof(chunk), fp) != NULL) {


        if (chunk[0]=='a' && chunk[9]=='s')
        {
            char* linea = ottieni_distanza(chunk);
            root = insert(root, distanza,linea);
            if (inserito == 1)
            {
                // aggiungo le auto
                // ora inserisco le auto presenti in linea
                char delimiter[] = " ";
                char* token, *context;
                token = strtok_r (linea, delimiter, &context);
                int numauto = atoi(token);
                appoggio->numcars = numauto;
                for (int i=0; i<numauto;i++)
                {
                    token = strtok_r (NULL, delimiter, &context);
                    int macchina = atoi(token);
                    insertAUTO(appoggio->cars,macchina,i);
                }
                inserito = 0;
                printf("aggiunta\n");
                totalestazioni++;
            }
            else
            {
                printf("non aggiunta\n");
            }
        }

        if (chunk[0]=='d')
        {

            ottieni_distanza(chunk);
            root = deleteNode(root, distanza);
            if (cancellato == 1)
            {
                cancellato = 0;
                printf("demolita\n");
                totalestazioni--;
            }
            else
            {
                printf("non demolita\n");
            }


        }
        if (chunk[0]=='a' && chunk[9]=='a')
        {
            char* linea = ottieni_distanza(chunk);
            // ora in distanza ho la stazione, prima la cerco
            // se la trovo inserisco, altrimenti non inserisco
            struct node* temp = search(root,distanza);
            if (temp == NULL)
                printf("non aggiunta\n");
            else
            {
                ottieni_auto(linea);
                insertAUTO(temp->cars,automobile,temp->numcars);
                temp->numcars++;
                printf("aggiunta\n");
            }
        }
        if (chunk[0]=='r')
        {
            char* linea = ottieni_distanza(chunk);
            // ora in distanza ho la stazione, prima la cerco
            // se la trovo inserisco, altrimenti non inserisco
            struct node* temp = search(root,distanza);
            if (temp == NULL)
                printf("non rottamata\n");
            else
            {
                // ora cerco l'auto sul nodo
                ottieni_auto(linea);
                int returnvalue = deleteAUTO(temp ->cars,automobile,temp ->numcars);
                if (returnvalue == 1)
                    temp ->numcars--;
            }
        }
        if (chunk[0]=='p')
        {
            //printf("nessun percorso\n");
            pianificapercorso(root, chunk);
        }


    }
    fclose(fp);
    // ora stampo la lista delle stazioni

    //inorder(root);
    //clock_t end = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    //time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    //printf("The elapsed time is %f seconds", time_spent);
    return 0;
}
