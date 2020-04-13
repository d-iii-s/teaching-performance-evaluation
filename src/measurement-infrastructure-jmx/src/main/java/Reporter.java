public class Reporter implements ReporterMBean {

    private Worker worker;

    public Reporter (Worker argWorker) {
        worker = argWorker;
    }

    public long getValue () {
        return worker.value;
    }

    public void reset () {
        worker.base = System.currentTimeMillis ();
    }
}
