Stock images go here (not committed). Each target's `target.toml` names its
files and pins the prog by sha256.

| File | Target | sha256 |
|---|---|---|
| `T6EGLBU01_BIN.cpt` | B13200091 prog | `837eb18f4180fe0d0124cfd90ff610067b1de40eba3be3545fc9108899a2f116` |
| `B132E0091_TAB.cpt` | B13200091 stock cal (MY11 FED) | `22457c0d65274b2715f2d3fb31a764931f9345335630d54a74ece47c9974fe8d` |
| `T6EVRGT430E01_BIN.cpt` | C132E0278 prog (USDM-patched) | `e3a7868cd4685b59919b7b79dc4b3f190ff7df030c2137f90e89fd975c41bc31` |

`.cpt` files are the raw region contents (prog from 0x40000, cal from
0x20000), as extracted from a CRP or dumped from the ECU.
