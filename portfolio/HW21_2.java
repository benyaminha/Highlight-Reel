

/*
     CIST 004B1 Fall 2022
     HW week 4 problem 2
     Description: counts the number of times an integer appears in an input
     Input: int
     Output: int
     Student: Benyamin Ha
     Known bugs: none.
     Date: 02.25.2023
*/
import java.util.*;
public class HW21_2{
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        Map<Integer, Integer> map = new HashMap<>(); 
    
        int highValue = 0;

        while(!input.hasNext("0")) {
            int currentInt = input.nextInt();
            int addToValue = map.containsKey(currentInt) ? map.get(currentInt) + 1 : 1; 
            map.put(currentInt, addToValue); 
            if(addToValue > highValue) {
                highValue = addToValue;
            }
        }
        
        Set<Integer> keySet = map.keySet(); 

        for(Integer i : keySet) {
            if(map.get(i) == highValue){
                System.out.print(i.toString() + ' ');
            }
        }
    }
}


/* INPUT: 9 9 9 2 2 2 3 4 5 6 0
 * OUTPUT: 2 9 
 */
