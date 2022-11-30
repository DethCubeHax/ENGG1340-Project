check if it is in the grid:
for ( int i = 0 ; i < SIZE ; i++)
for ( int j = 0 ; i < 3 ; j++)

check if the number in:
[i][j]     [i][j+1]     [i][j+2]
[i+3][j]   [i+3][j+1]   [i+3][j+2]
[i+6][j]   [i+6][j+1]   [i+6][j+2]

notIN=true;
for ( int i = 0 ; i < SIZE ; i+=3){
    for ( int j = 0 ; i < 3 ; j++){
        if ( [i][j] == number ){
            notIn = false;
            break;
        }
    }
}


check if it is in the row:
for ( int j = 0 ; j < SIZE ; j++)

check if it is in the column:
for ( int i = 0 ; i < SIZE ; i++)


