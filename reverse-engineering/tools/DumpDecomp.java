import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;

public class DumpDecomp extends GhidraScript {
    static String[] KW = {"Race", "Sidetone", "ChatMix", "MicVolume", "StandAlone", "Nv",
        "Peq", "Anc", "Battery", "Voice", "Wear", "Notification", "FactoryReset",
        "genRaw", "Packet", "Brightness", "Balance", "Guidance", "BusyLight"};

    public void run() throws Exception {
        String out = System.getProperty("user.home") + "/jbl-re/decomp_dump.c";
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int count = 0;
        PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(out)));
        while (it.hasNext()) {
            Function f = it.next();
            String n = f.getName();
            boolean hit = false;
            for (String k : KW) if (n.toLowerCase().contains(k.toLowerCase())) { hit = true; break; }
            if (!hit) continue;
            DecompileResults r = di.decompileFunction(f, 60, monitor);
            if (r.decompileCompleted()) {
                w.println("// ==== " + n + " @ " + f.getEntryPoint() + " ====");
                w.println(r.getDecompiledFunction().getC());
                w.println();
                count++;
            }
        }
        w.close();
        println("DUMPED " + count + " functions to " + out);
    }
}
