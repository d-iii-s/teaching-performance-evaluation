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

import java.io.PrintStream;
import java.io.FileOutputStream;

import org.objectweb.asm.Opcodes;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;

// Inheritance used for short access to opcode constants.
public class GeneratorWithWriter implements Opcodes {

    public static void main (final String args []) throws Exception {

        // ClassWriter for the Example class that inherits from the Object class.
        ClassWriter cw = new ClassWriter (0);
        cw.visit (V1_1, ACC_PUBLIC, "Example", null, "java/lang/Object", null);

        // MethodWriter for the constructor.
        MethodVisitor mw = cw.visitMethod (ACC_PUBLIC, "<init>", "()V", null, null);
        mw.visitVarInsn (ALOAD, 0);
        mw.visitMethodInsn (INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
        mw.visitInsn (RETURN);
        // Maximum one stack element, one local variable.
        mw.visitMaxs (1, 1);
        mw.visitEnd ();

        // MethodWriter for the 'main' method.
        mw = cw.visitMethod (ACC_PUBLIC + ACC_STATIC, "main", "([Ljava/lang/String;)V", null, null);
        mw.visitFieldInsn (GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
        mw.visitLdcInsn ("Hello world !");
        mw.visitMethodInsn (INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V", false);
        mw.visitInsn (RETURN);
        // Maximum two stack elements, two local variables.
        mw.visitMaxs (2, 2);
        mw.visitEnd ();

        // Write the bytecode to file.
        byte [] code = cw.toByteArray ();
        FileOutputStream fos = new FileOutputStream ("target/classes/ExampleWithWriter.class");
        fos.write (code);
        fos.close ();
    }
}
