// Decompile one or more function RVAs and print identity evidence.
// Usage: analyzeHeadless <proj> bfme -process lotrbfme.exe -noanalysis \
//   -scriptPath tools/ghidra -postScript decompile_function.java 0x82190
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;

public class decompile_function extends GhidraScript {
    public void run() throws Exception {
        if (getScriptArgs().length == 0) {
            throw new IllegalArgumentException("pass at least one function RVA");
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        Address imageBase = currentProgram.getImageBase();
        for (String raw : getScriptArgs()) {
            long rva = Long.decode(raw);
            Address address = imageBase.add(rva);
            Function function = getFunctionAt(address);
            if (function == null) {
                println("RVA " + raw + ": no Ghidra function starts at " + address);
                continue;
            }
            println("RVA " + raw + " " + function.getName() + " @ " + address
                    + " size " + function.getBody().getNumAddresses());
            println("REFERENCES TO ENTRY:");
            ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(address);
            while (refs.hasNext()) {
                Reference ref = refs.next();
                Function owner = getFunctionContaining(ref.getFromAddress());
                println("  " + ref.getFromAddress() + " " + ref.getReferenceType() + " "
                        + (owner == null ? "<data>" : owner.getName() + "@" + owner.getEntryPoint()));
            }
            println("DIRECT CALLEES:");
            for (Function callee : function.getCalledFunctions(monitor)) {
                long calleeRva = callee.getEntryPoint().subtract(imageBase);
                println("  0x" + Long.toHexString(calleeRva) + " " + callee.getName());
            }
            DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
            println("DECOMPILE:");
            println(result.decompileCompleted()
                    ? result.getDecompiledFunction().getC()
                    : "FAILED: " + result.getErrorMessage());
        }
        decompiler.dispose();
    }
}
