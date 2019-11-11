#!/bin/bash

svm-scale -l -1 -u 1 -s ranges.txt arquivoGeral.libsvm > arquivoGeral.scale.libsvm
echo "Scale ... ok"
sort -R  arquivoGeral.scale.libsvm >  arquivoGeral.scale.libsvm.random
echo "Sort ... ok"
cat arquivoGeral.scale.libsvm.random | grep "1 1:" | head -16 > trnArquivoGeral.scale.libsvm.random.class1
echo "trn_1 ... ok"
cat arquivoGeral.scale.libsvm.random | grep "0 1:" | head -100 > trnArquivoGeral.scale.libsvm.random.class0
echo "trn_0 ... ok"
cat arquivoGeral.scale.libsvm.random | grep "0 1:" | tail -100 > tstArquivoGeral.scale.libsvm.random.class0 
echo "tst_0 ... ok"
cat arquivoGeral.scale.libsvm.random | grep "1 1:" | tail -8 > tstArquivoGeral.scale.libsvm.random.class1
echo "tst_1 ... ok"
cat trnArquivoGeral.scale.libsvm.random.class0 > trnFinal.libsvm
cat trnArquivoGeral.scale.libsvm.random.class1 >> trnFinal.libsvm
echo "trnFinal ... ok"
cat tstArquivoGeral.scale.libsvm.random.class0 > tstFinal.libsvm
cat tstArquivoGeral.scale.libsvm.random.class1 >> tstFinal.libsvm 
echo "tstFinal ... ok"
python ~/Documentos/projeto/libsvm-3.17/tools/grid.py ~/workspaceC++/_libSVM_/testeImgProcess/trnFinal.libsvm > ~/workspaceC++/_libSVM_/testeImgProcess/grid_py_arquivoGeral
echo "grid.py ... ok"
