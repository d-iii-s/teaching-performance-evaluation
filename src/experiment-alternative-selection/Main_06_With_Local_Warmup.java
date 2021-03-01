public class Main_06_With_Local_Warmup {

	static int N = 1000000;

	private static long test (BenchIface b) {
		long time = System.nanoTime ();
		for (int i = 0 ; i < N ; i++) {
			b.method (i);
		}
		return (System.nanoTime () - time);
	}

	public static void main (String[] params) {

		if (params.length == 1) {
			N = Integer.parseInt (params[0]);
		}

		test (new BenchImpl1 ());
		long time1 = test (new BenchImpl1 ());

		test (new BenchImpl2 ());
		long time2 = test (new BenchImpl2 ());

		System.out.println ('count,time,version');
		System.out.println (N + "," + time1 + ",one");
		System.out.println (N + "," + time2 + ",two");
	}
}
