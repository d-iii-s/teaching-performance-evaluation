class SimpleNanotime {

    public static void main (String [] arguments) {

        final int COUNT = 100000;
        long [] results = new long [COUNT];

        for (int i = 0 ; i < COUNT ; i ++) {
            results [i] = System.nanoTime ();
        }

        System.out.println ("index,time");
        for (int i = 0 ; i < COUNT ; i ++) {
            System.out.println (i + "," + results [i]);
        }
    }
}
