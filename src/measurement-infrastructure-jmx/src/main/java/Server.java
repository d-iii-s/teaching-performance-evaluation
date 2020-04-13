import java.lang.management.ManagementFactory;
import javax.management.MBeanServer;
import javax.management.ObjectName;

public class Server {
    public static void main (String [] args) {

        Worker worker = new Worker ();
        worker.start ();

        Reporter bean = new Reporter (worker);

        try {

            MBeanServer mbs = ManagementFactory.getPlatformMBeanServer ();
            ObjectName name = new ObjectName ("org.example:type=Reporter");
            mbs.registerMBean (bean, name);

        } catch (Exception e) {
            System.out.println (e);
        }
    }
}
