version 1.0
# this file has been automatically generated by the OpenQL compiler please do not modify it manually.
qubits 7
.aKernel

    { x q[0] | x q[1] | x q[2] | x q[3] | x q[4] }
    { cnot q[0],q[2] | cnot q[0],q[3] | cnot q[1],q[3] | cnot q[1],q[4] }
    wait 2
    { x q[5] | x q[6] }
    { cnot q[2],q[0] | cnot q[2],q[5] | cnot q[3],q[0] | cnot q[3],q[1] | cnot q[3],q[5] | cnot q[3],q[6] | cnot q[4],q[1] | cnot q[4],q[6] }
    wait 3
    { cnot q[5],q[2] | cnot q[5],q[3] | cnot q[6],q[3] | cnot q[6],q[4] }
    wait 3
    { x q[0] | x q[1] | x q[2] | x q[3] | x q[4] | x q[5] | x q[6] }
