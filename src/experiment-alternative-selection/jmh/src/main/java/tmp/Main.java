package tmp;

import java.util.concurrent.TimeUnit;
import org.openjdk.jmh.annotations.*;

@State (Scope.Thread)
public class Main {

	BenchIface b1;
	BenchIface b2;

	@Setup
	public void setup () {
		b1 = new BenchImpl1 ();
		b2 = new BenchImpl2 ();
	}

	@Benchmark
	@BenchmarkMode (Mode.AverageTime)
	@OutputTimeUnit (TimeUnit.NANOSECONDS)
	public void callImpl1 () {
		b1.method (0);
	}

	@Benchmark
	@BenchmarkMode (Mode.AverageTime)
	@OutputTimeUnit (TimeUnit.NANOSECONDS)
	public void callImpl2 () {
		b2.method (0);
	}
}
