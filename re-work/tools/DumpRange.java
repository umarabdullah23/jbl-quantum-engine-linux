import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.*;
import java.io.*;

public class DumpRange extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        long start = Long.parseLong(args[0].replaceFirst("^0x", ""), 16);
        long end = Long.parseLong(args[1].replaceFirst("^0x", ""), 16);
        String out = args[2];
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        AddressSet set = new AddressSet(currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(start),
                                        currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(end));
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(set, true);
        int count = 0;
        PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(out)));
        while (it.hasNext()) {
            Function f = it.next();
            DecompileResults r = di.decompileFunction(f, 90, monitor);
            if (r.decompileCompleted()) {
                w.println("// ==== " + f.getName() + " @ " + f.getEntryPoint() + " ====");
                w.println(r.getDecompiledFunction().getC());
                w.println();
                count++;
            }
        }
        w.close();
        println("DUMPED " + count + " functions to " + out);
    }
}
