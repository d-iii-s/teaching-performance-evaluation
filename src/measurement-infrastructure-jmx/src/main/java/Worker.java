public class Worker extends Thread {

    public long value = 0;
    public long base = 0;

    public void run () {
        while (true) {
            // Keep updating the value made available through the bean.
            try { Thread.sleep (100); }
            catch (InterruptedException e) { };
            long time = System.currentTimeMillis ();
            value = Math.round (Math.sin ((time - base) / 10000.0) * 100.0);
        }
    }
}
