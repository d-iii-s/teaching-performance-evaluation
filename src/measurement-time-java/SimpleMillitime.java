class SimpleMillitime {

    public static void main (String [] arguments) {

        final int COUNT = 100000;
        long [] results = new long [COUNT];

        for (int i = 0 ; i < COUNT ; i ++) {
            results [i] = System.currentTimeMillis ();
        }

        for (int i = 0 ; i < COUNT ; i ++) {
            System.out.println (results [i]);
        }
    }
}
