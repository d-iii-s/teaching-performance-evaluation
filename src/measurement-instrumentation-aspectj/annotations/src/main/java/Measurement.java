import org.aspectj.lang.ProceedingJoinPoint;

import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;

@Aspect
public class Measurement {

    @Pointcut ("execution (* Main.* (..))")
    void allMainMethods () {};

    @Around ("allMainMethods ()")
    public Object measureTime (ProceedingJoinPoint thisJoinPoint) {

        Object result = null;
        long timeBefore = System.nanoTime ();
        try { result = thisJoinPoint.proceed (); }
        catch (Throwable t) { };
        long timeAfter = System.nanoTime ();
        System.out.println ("Method duration " + (timeAfter - timeBefore) + " ns.");

        return (result);
    }
}
