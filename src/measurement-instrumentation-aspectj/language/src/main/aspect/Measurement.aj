aspect Measurement {

    pointcut allMainMethods (): execution (* Main.* (..));

    Object around (): allMainMethods () {

        Object result = null;
        long timeBefore = System.nanoTime ();
        try { result = proceed (); }
        catch (Throwable t) { };
        long timeAfter = System.nanoTime ();
        System.out.println ("Method duration " + (timeAfter - timeBefore) + " ns.");

        return (result);
    }
}
