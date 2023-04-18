//solution for cow genomics analyzation lab

import java.util.*;

public class Geonomics {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int N = input.nextInt();
        int M = input.nextInt();

        String spotty[] = new String[N];
        for(int i = 0; i < N; i++) {
            spotty[i] = input.next();
        }

        String plain[] = new String[N];
        for(int i = 0; i < N; i++) {
            plain[i] = input.next();
        }

        int counter = 0;
        boolean isPotentialLocation = true;
        for(int i = 0; i < M; i++) {
        Set<Character> spottyGenes = new HashSet<>(); 
            for(int j = 0; j < N; j++) {
                spottyGenes.add(spotty[j].charAt(i));
                if(spottyGenes.size() == 4){
                    isPotentialLocation = false;
                    break;
                }
            }



            if(isPotentialLocation) {
                for(int j = 0; j < N; j++) {
                    if(spottyGenes.contains(plain[j].charAt(i))) {
                        isPotentialLocation = false;
                        break;
                     }
                }
            }

            if(isPotentialLocation) {
                counter++;
            }

            else{
                isPotentialLocation = true;

            }
        }

        System.out.println(counter);
    }
}
