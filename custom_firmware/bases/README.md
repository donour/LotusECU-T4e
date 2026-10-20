Stock images go here (not committed). Each target's `target.toml` names its
files and pins the prog by sha256.

| File | Target | sha256 | Source |
|---|---|---|---|
| `T6EGLBU01_BIN.cpt` | B13200091 prog | `837eb18f4180fe0d0124cfd90ff610067b1de40eba3be3545fc9108899a2f116` | official `2011NA/B132E0091.CRP` |
| `B132E0091_TAB.cpt` | B13200091 stock cal (MY11 FED) | `22457c0d65274b2715f2d3fb31a764931f9345335630d54a74ece47c9974fe8d` | official `2011NA/B132E0091.CRP` |
| `T6EVRGT430E01_BIN.cpt` | C132E0278 prog (factory) | `b11a1812dc742ace61eb190e41d6435deef8b908158e5090d14ee1a4f4c52aea` | official `2019GT430/C132E0278.CRP` |

`.cpt` files are the raw region contents (prog from 0x40000, cal from
0x20000), as extracted from a CRP or dumped from the ECU.
