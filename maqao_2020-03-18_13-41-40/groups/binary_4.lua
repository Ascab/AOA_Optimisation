_group = {
  {
    group_size = 2,
    pattern = "LL",
    opcodes = "MOVSS,MOVSS,",
    offsets = "0,0,",
    addresses = "0xbd5,0xcaf,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 8,
    accessed_memory_nooverlap = 4,
    accessed_memory_overlap = 4,
    span = 4,
    head = 0,
    unroll_factor = 2,
  },
  {
    group_size = 2,
    pattern = "LL",
    opcodes = "MOVSS,MOVSS,",
    offsets = "0,0,",
    addresses = "0xbae,0xc95,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 8,
    accessed_memory_nooverlap = 4,
    accessed_memory_overlap = 4,
    span = 4,
    head = 0,
    unroll_factor = 2,
  },
  {
    group_size = 5,
    pattern = "LLLLL",
    opcodes = "MOVSS,MOVSS,MOVSS,MOVSS,MOVSS,",
    offsets = "0,0,0,0,0,",
    addresses = "0xb4e,0xb71,0xb98,0xc34,0xc7f,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 20,
    accessed_memory_nooverlap = 4,
    accessed_memory_overlap = 16,
    span = 4,
    head = 0,
    unroll_factor = 5,
  },
  {
    group_size = 2,
    pattern = "LL",
    opcodes = "MOVSS,MOVSS,",
    offsets = "551,356,",
    addresses = "0xb75,0xc38,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 8,
    accessed_memory_nooverlap = 8,
    accessed_memory_overlap = 0,
    span = 199,
    head = 0,
    unroll_factor = 2,
  },
  {
    group_size = 4,
    pattern = "LSLS",
    opcodes = "MOVSS,MOVSS,MOVSS,MOVSS,",
    offsets = "0,0,0,0,",
    addresses = "0xc09,0xc19,0xc69,0xcbb,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 16,
    accessed_memory_nooverlap = 4,
    accessed_memory_overlap = 12,
    span = 4,
    head = 0,
    unroll_factor = 1,
  },
  {
    group_size = 29,
    pattern = "LLLLLLLLLLLLLLLLLLLLLLLLLLLLS",
    opcodes = "MOV,CMP,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,MOV,ADD,",
    offsets = "-8,-20,-8,-40,-8,-40,-8,-40,-4,-56,-8,-40,-8,-48,-8,-32,-8,-32,-8,-32,-8,-32,-8,-40,-4,-56,-8,-48,-8,",
    addresses = "0xcc3,0xcc6,0xb3c,0xb47,0xb5f,0xb6a,0xb86,0xb91,0xb9c,0xba7,0xc22,0xc2d,0xbc3,0xbce,0xbe5,0xbf0,0xbf7,0xc02,0xc45,0xc50,0xc57,0xc62,0xc6d,0xc78,0xc83,0xc8e,0xc9d,0xca8,0xcbf,",
    stride_status = "Not mono block loop",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 168,
    accessed_memory_nooverlap = 44,
    accessed_memory_overlap = 124,
    span = 56,
    head = 0,
    unroll_factor = 1,
  },
}
