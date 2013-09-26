#include <stdio.h>
#include <string.h>
#include <ctype.h>

    int e[4][4] = { {9, 12, 23,  1},        //populated Encryption matrix
                    {24,  5, 24, 19},       //declared as global
                    {13,  2, 21, 13},
                    {1 ,  3, 25, 15}};
                    
    int d[4][4] = { {10, 12,  8, 12},        //poulated Decryption matrix
                    {6, 21, 23, 13 },       //declared as global
                    {20, 11, 19,  5},
                    {17, 25, 27, 27} };
                    
    int n = 29;     //modulus as global
                    
                    
/*Function to return number related to letter input*/
int find_num ( char input )
{
        char letters[29] = {    '*', 'A', 'B', 'C', 'D', 'E',
                                'F', 'G', 'H', 'I', 'J', 'K', 
                                'L', 'M', 'N', 'O', 'P', 'Q', 
                                'R', 'S', 'T', 'U', 'V', 'W', 
                                'X', 'Y', 'Z', ']', '%' };
        
        int i;
                             
        for ( i = 0; i < 29; i ++ )
        {
            if ( input == letters[i] )
            {
                return ( i );   //return corresponding number
            }
        }
        return NULL;
}

/*function to find character related to number input*/
char  find_char ( int input )
{
        char letters[29] = { '*', 'A', 'B', 'C', 'D', 'E',
                             'F', 'G', 'H', 'I', 'J', 'K',
                             'L', 'M', 'N', 'O', 'P', 'Q',
                             'R', 'S', 'T', 'U', 'V', 'W',
                             'X', 'Y', 'Z', ']', '%' };
                             
        return ( letters[input] );
}

/*function to encrypt a block*/
void encrypt( char *plain, char *cypher)
{

                 
    int i;
    int block[4];
    int temp;
                    
    //fill a block of 4 with numbers related to letters
    for ( i = 0; i < 4; i++ )
    {
        block[i] = find_num( plain[i] );
    }
    
    int j, row_total;
    
    /*caluclate mod array of numbers*/
    for ( i = 0; i < 4; i++ )
    {
        row_total = 0;
        
        for ( j = 0; j < 4; j++ )
        {
            row_total = row_total + ( e[i][j] * block[j] ); //multiplying by encrypt matrix and adding together
        }
        
        temp = row_total%n;
        cypher[i] = find_char ( temp );
    }
    cypher[i] = NULL;
    
}

/*function to decrypt a block*/
void decrypt( char *cypher, char *plain )
{
    int block[4];
    
    int i;
    int temp;
    
    //fill a block of 4 with numbers related to letters
    for ( i = 0; i < 4; i++ )
    {
        block[i] = find_num( cypher[i] );
    }
    
    int j, row_total;
    
    /*caluclate mod array of numbers*/
    for ( i = 0; i < 4; i++ )
    {
        row_total = 0;
        
        for ( j = 0; j < 4; j++ )
        {
            row_total = row_total + ( d[i][j] * block[j] );
        }
        
        temp = row_total%n;
        plain[i] = find_char ( temp );
    }
    plain[i] = NULL;
    
}

/*function to check if string is divisable by 4, if not elements are added to the end to make it so*/
void parse ( char *str_input, int *len )
{
    int j;
    int length = *len ;
    
    /*convert to upper case if required*/
    for ( j = 0; j < length; j++ )
    {
        str_input[j] = toupper(str_input[j] );
    }

    if ( length%4 == 0 )       //if already divisable by 4, simply return
    {
        return;
    }
    else                        //if not, add some character(s) to the end of string
    {
        int remain_letters = 4 - ( length%4 );
        int i;
        
        for ( i = 0; i < remain_letters; i++ )
        {
            str_input[length + i ] = '*';
            length++;
        }
        str_input[length + i] = NULL;
    }
    
    *len = length ;

}
//function to encrypt message
void option1( void )
{
    char str_input[200] = { NULL };        //input string
    char str_output[200] = { NULL };       //output string
    char str_output2[200] = { NULL };      //output string
    
    int length;
    int i = 0, j;
    
    char cypher[5];
    char plain[5];
    
            printf("\n");
            printf("String (plaintext): ");
            fflush(stdin);
            gets( str_input );
            fflush(stdin);
            length = strlen( str_input );   //get length of string
            
            parse( str_input, &length );    //make string divisable by 4
  
            while ( i < length )
            {
                for ( j = 0; j < 4; j++ )
                {
                    plain[j] = str_input[i];
                    i++;
                }
                
                plain[j] = NULL;
                encrypt( plain, cypher ); //encrypt block
                               
                if ( i < 4 )
                {
                    strcpy( str_output, cypher );
                }
                else
                {
                    strcat( str_output, cypher );   //concatenate to output string    
                }
                
            }   
            
            printf("Encrypted (cypher): %s", str_output );
            
            i = 0;
            
            
            while ( i < length )
            {
                for ( j = 0; j < 4; j++ )       //decrypt in block of 4
                {
                    cypher[j] = str_output[i];
                    i++;
                }
                
                decrypt( cypher, plain );      //decrypt block
                
                if ( i < 4 )
                {
                    strcpy( str_output2, plain );
                }
                else
                {
                    strcat( str_output2, plain );   //concatenate to output string
                }
                
            }
            
            printf("\nDecrypted string: %s \n\n", str_output2 ); 
            
            
            str_output[0] = NULL;
}
//function to decrypt message
void option2 ( void )
{
    char str_input[200] = { NULL };        //input string
    char str_output[200] = { NULL };       //output string
    char str_output[200] = {NULL};         //out string
    
    int length;
    int i = 0, j;
    
    char cypher[5];
    char plain[5];
    
            printf("\n");
            printf("Please enter string to decrypt: \n");
            fflush(stdin);
            gets( str_input );
            fflush(stdin);
            length = strlen( str_input );   //get length of string
            parse( str_input, &length );    //make string divisable by 4
            
            while ( i < length )
            {
                for ( j = 0; j < 4; j++ )
                {
                    cypher[j] = str_input[i];
                    i++;
                }
                
                decrypt( cypher, plain );      //decrypt block
                if ( i < 4 )
                {
                    strcpy( str_output, plain );
                }
                else
                {
                    strcat( str_output, plain );   //concatenate to output string
                }
                
            }
            
            printf("\nDecrypted string: %s \n\n", str_output ); 
}
//function to check/print idenity matrix
void option3 ( void )
{
    int identity[4][4] = { {0} };   //initilise to zero
    int i, j, k = 0;
    int temp = 0;
    
    //calculate identity matrix 
    while ( k < 4 )
    {
        for ( i = 0; i < 4; i ++ )
        {
            for ( j = 0; j < 4; j++ )
            {
                temp = temp + ( d[k][j] * e[j][i] );    //mutiple D by E in nested loops
            }
            identity[k][i] = temp % n;  //store modulus of result in identity array
            temp = 0;   //reset temp for next calulation
        }
        k++;   
    }
    
    printf("\n");
    
    //print identity matrix to screen
    for ( i = 0; i < 4; i ++ )
    {
        for (j = 0; j < 4; j++ )
        {
            identity[i][j] = identity[i][j]%n;
            printf("\t%d", identity[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
main()
{
    char option;

    
    printf("Please note: additional '*' maybe encoded to the end of strings to \n");
    printf("allow for encryption in blocks of 4\n\n");
    /*Prompt user and take in string to be encrypted/decrypted*/
    
    while (1)
    {

        printf("Press one and enter to encrypt a message:\n");
        printf("Press two and enter to decrypt a message:\n");
        printf("Press three and enter to check and print identity matrix:\n");
        fflush(stdin);
        option = getchar();
        
        switch( option )
        {
        case '1':
            option1();
            break;
        case '2':
            option2();
            break;
        case '3':
            option3();
            break;
        default:
            printf("Invalid Option chosen\n");
            break;
        }
    }
     
}