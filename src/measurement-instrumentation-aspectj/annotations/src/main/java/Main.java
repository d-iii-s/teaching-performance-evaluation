import java.util.Random;

class Main {
    static Random random = new Random ();

    static void someMethod () {
        int sleepDuration = random.nextInt (1000);
        System.out.println ("Sleeping for " + sleepDuration + " ms.");
        try { Thread.sleep (sleepDuration); }
        catch (InterruptedException e) { };
    }

    public static void main (String [] arguments) {
        for (int i = 0 ; i < 10 ; i ++) someMethod ();
    }
}
