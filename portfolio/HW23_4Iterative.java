//given an infinite number spiral, find the number at a specified column and row
import java.util.*; 

public class HW23_4Iterative {
    public static void main(String[] args) {
        System.out.println(numberSpiral(12345678,87654321)); 
    }

    static long numberSpiral(int column, int row) {
        long one = 1L;
        if(column >= row) {
            if(column % 2 == 0) {
                long startingNumber = findColumn(column);

                return startingNumber - (long)row + one;
            } 
            else {
                long startingNumber = findColumn(column - 1);
                return startingNumber  + row -1;
            }
        }

        else {
            if(row % 2 == 0) {

                long startingNumber = findRow(row -1);
                return startingNumber + column;
            } 
            else {
                long startingNumber = findRow(row);
                return startingNumber - column + 1;
            }
        }
    }

    static long findRow(int x) {
        if(x == 1) {
            return 1;
        }

        long returnThis = 1;
        for(int i = 3; i < x+1; i++) {
            if(i % 2 != 0) {
                int addToReturn = 2*i + 2*(i-1) -2;
                returnThis += addToReturn;  
            } 
        }

        return returnThis;
    }

    static long findColumn(int x) {
        if(x == 1) {
            return 1;
        }
        long returnThis = 1;
            
        for(int i = 2; i < x+1; i++) {
            if(i % 2 == 0 && i != 0) {
                long addToReturn = 2*i + 2*(i-1) - 2; 
                returnThis += addToReturn; 
            }
        }
        return returnThis;
    }
}

// input 1:6679196792954254 
// input 2:7683279977625364 
