// Ghidra headless script: export the full function inventory (rva,size,name).
// Usage: analyzeHeadless <proj> bfme -process lotrbfme.exe -noanalysis \
//          -scriptPath tools/ghidra -postScript list_functions.java <out.csv>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.FileWriter;
import java.io.PrintWriter;

public class list_functions extends GhidraScript {
    public void run() throws Exception {
        String out = getScriptArgs().length > 0 ? getScriptArgs()[0] : "ghidra_functions.csv";
        PrintWriter w = new PrintWriter(new FileWriter(out));
        w.println("rva,size,name");
        long base = currentProgram.getImageBase().getOffset();
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int n = 0;
        while (it.hasNext()) {
            Function f = it.next();
            long size = f.getBody().getNumAddresses();
            long rva = f.getEntryPoint().getOffset() - base;
            w.printf("0x%X,%d,%s%n", rva, size, f.getName().replace(",", ";"));
            n++;
        }
        w.close();
        println("wrote " + n + " functions to " + out);
    }
}
