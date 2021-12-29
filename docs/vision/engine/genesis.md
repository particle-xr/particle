---
title: Genesis state
---
Genesis state will be a file used as the starting point for worlds. For example, the world of Arda will have a genesis state file `arda.genesis.xr`. Files using the `.xr` extension will be considered "world state files". Such files will be binary files containing the compiled initial "shape" of the world.

You can imagine that the workflow for creating worlds will thus be using either an IDE (akin to Unity and Unreal's dedicated IDEs) or writing code that defines the world in terms of its elemental makeup. Once you are satisfied with your world, you will export the compiled .xr state file, thus creating the *genesis state*. When a world is first deployed, the genesis state file will be used to "bootstrap" the world.

Worlds can thus be created as one of two flavors:
1. Persistent worlds in which the genesis state is purely the "start of time". Such worlds will then undergo transformations as time continues. Periodically, persistent worlds will export snapshots of themselves in the form of `arda.TIMESTAMP.xr`. These files will thence be our way of persisting world state across e.g. deployments.
2. Ephemeral (?) worlds in which the genesis state is used to bootstrap the world each time it is deployed. Such worlds will still undergo change over time, but these changes will **not** persist across deployments, sessions, etc. This world type might be suitable for personal chatrooms, in which the hoster:
    - does not wish to maintain a history of their simulation's state, e.g. for cost reasons associated with the storage required to do so
    - does not care about persistent state (for whatever reason)
    - *wants* their simulation to be ephemeral, for example perhaps the integrity of the simulation hinges on the fact that it is exactly the same at the onset for every user (e.g. perhaps it is a custom, non-collaborative (i.e. no shared sessions) "quest")

An interesting extension is then: could a world have mixed genesis/snapshot states? For example, "quest simulations" within an otherwise persistent world?
