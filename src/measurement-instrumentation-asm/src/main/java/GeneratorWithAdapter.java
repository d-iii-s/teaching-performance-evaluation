/*
 * The following code is based on an example from the ASM distribution.
 *
 * Copyright (c) 2000-2011 INRIA, France Telecom
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.io.FileOutputStream;
import java.io.PrintStream;

import org.objectweb.asm.Type;
import org.objectweb.asm.Opcodes;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.commons.GeneratorAdapter;
import org.objectweb.asm.commons.Method;

// Inheritance used for short access to opcode constants.
public class GeneratorWithAdapter implements Opcodes {

    public static void main (String args []) throws Exception {

        // ClassWriter for the Example class that inherits from the Object class.
        ClassWriter cw = new ClassWriter (ClassWriter.COMPUTE_MAXS);
        cw.visit (V1_1, ACC_PUBLIC, "Example", null, "java/lang/Object", null);

        // GeneratorAdapter for the constructor.
        Method m = Method.getMethod ("void <init> ()");
        GeneratorAdapter mg = new GeneratorAdapter (ACC_PUBLIC, m, null, null, cw);
        mg.loadThis ();
        mg.invokeConstructor (Type.getType (Object.class), m);
        mg.returnValue ();
        mg.endMethod ();

        // GeneratorAdapter for the 'main' method.
        m = Method.getMethod ("void main (String[])");
        mg = new GeneratorAdapter (ACC_PUBLIC + ACC_STATIC, m, null, null, cw);
        mg.getStatic (Type.getType (System.class), "out", Type.getType (PrintStream.class));
        mg.push ("Hello world !");
        mg.invokeVirtual (Type.getType (PrintStream.class), Method.getMethod ("void println (String)"));
        mg.returnValue ();
        mg.endMethod ();

        cw.visitEnd ();

        // Write the bytecode to file.
        byte [] code = cw.toByteArray ();
        FileOutputStream fos = new FileOutputStream ("target/classes/ExampleWithAdapter.class");
        fos.write (code);
        fos.close ();
    }
}
