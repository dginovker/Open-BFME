// Ghidra headless script: export each string literal and the RVAs of functions that
// reference it. Powers string-based identification (anchor anonymous functions to the
// Generals source file/function whose strings they reference).
// Usage: analyzeHeadless <proj> bfme -process lotrbfme.exe -noanalysis \
//          -scriptPath tools/ghidra -postScript list_string_xrefs.java <out.tsv>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.HashSet;

public class list_string_xrefs extends GhidraScript {
    public void run() throws Exception {
        String out = getScriptArgs().length > 0 ? getScriptArgs()[0] : "string_xrefs.tsv";
        PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(out)));
        long base = currentProgram.getImageBase().getOffset();
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        int n = 0;
        DataIterator di = currentProgram.getListing().getDefinedData(true);
        while (di.hasNext()) {
            Data d = di.next();
            Object v = d.getValue();
            if (!(v instanceof String)) continue;
            String s = ((String) v).replace("\t", " ").replace("\n", " ").replace("\r", " ");
            if (s.length() < 5) continue;
            HashSet<Long> seen = new HashSet<Long>();
            StringBuilder rvas = new StringBuilder();
            ReferenceIterator it = rm.getReferencesTo(d.getMinAddress());
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = fm.getFunctionContaining(r.getFromAddress());
                if (f != null && seen.add(f.getEntryPoint().getOffset())) {
                    if (rvas.length() > 0) rvas.append(",");
                    rvas.append("0x").append(Long.toHexString(f.getEntryPoint().getOffset() - base));
                }
            }
            if (rvas.length() > 0) { w.println(s + "\t" + rvas.toString()); n++; }
        }
        w.close();
        println("wrote " + n + " string xrefs to " + out);
    }
}
