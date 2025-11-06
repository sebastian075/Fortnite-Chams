    if (settings::visuals::chams) {
                auto SkeletalMeshes = Ioctl.read<ttarray<uint64_t>>(player.Pawn + 0x60b0);
                int skeletalMeshSize = SkeletalMeshes.count;
                for (int i = 0; i < skeletalMeshSize; i++) {
                    auto mesh_addr = SkeletalMeshes.Get(i);
                    if (!mesh_addr || !is_valid(mesh_addr)) continue;
 
                    int stencil_value = 11;  // red
                    Ioctl.write<int>(mesh_addr + 0x2A4, stencil_value); 
 
                    uint8_t state_byte = Ioctl.read<uint8_t>(mesh_addr + 0x95);
                    uint8_t new_state_byte = state_byte | (1 << 0);
                    if (state_byte != new_state_byte) {
                        Ioctl.write<uint8_t>(mesh_addr + 0x95, new_state_byte);
                    }
 
                    uint8_t depth_flags = Ioctl.read<uint8_t>(mesh_addr + 0x271);
                    uint8_t new_depth_flags = depth_flags | (1 << 6);
                    if (depth_flags != new_depth_flags) {
                        Ioctl.write<uint8_t>(mesh_addr + 0x271, new_depth_flags); 
                    }
 
                    uint8_t replication = Ioctl.read<uint8_t>(mesh_addr + 0x5b);
                    uint8_t new_replication = replication | (1 << 3);
                    if (replication != new_replication) {
                        Ioctl.write<uint8_t>(mesh_addr + 0x5b, new_replication);
                    }
                }
            }
