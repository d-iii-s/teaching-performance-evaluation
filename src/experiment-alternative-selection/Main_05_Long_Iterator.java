public class Main_05_Long_Iterator {

	static long N = 1000000;

	private static long test (BenchIface b) {
		long time = System.nanoTime ();
		for (long i = 0 ; i < N ; i++) {
			b.method ((int) i);
		}
		return (System.nanoTime () - time);
	}

	public static void main (String[] params) {

		if (params.length == 1) {
			N = Long.parseLong (params[0]);
		}

		long time1 = test (new BenchImpl1 ());
		long time2 = test (new BenchImpl2 ());

		System.out.println ("count,time,version");
		System.out.println (N + "," + time1 + ",one");
		System.out.println (N + "," + time2 + ",two");
	}
}
