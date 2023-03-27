//
// Created by yuhao on 5/16/22.
//

#include "device_driver.h"

#ifndef INC_2021_TEMPLATE_SYZLANG_H
#define INC_2021_TEMPLATE_SYZLANG_H

namespace sd {
    const static std::string syscall_open[]{
            "openat$",
            "(fd const[AT_FDCWD], file ptr[in, string[\"/dev/",
            "\"]], flags flags[open_flags], mode const[0]) ",
            "syz_open_dev$",
            "(dev ptr[in, string[\"/dev/",
            "\"]], id intptr, flags flags[open_flags]) ",
    };

    const static std::string syscall_ioctl[]{
            "ioctl$",
            "(fd ",
            ", cmd const[",
            "], arg ",
            ")",
    };

    const static std::string copyright =
            Annotation_Symbol"Copyright 2018 syzkaller project authors. All rights reserved.\n"
            Annotation_Symbol"Use of this source code is governed by Apache 2 LICENSE that can be found in the LICENSE file.\n";
    const static std::string kernel_version =
            Annotation_Symbol"Code generated by SyzDescribe. DO NOT EDIT.\n"
            Annotation_Symbol"Code generated from linux ";

    const static std::string arches[][2]{
            "x86", "386",
            "x86_64", "amd64",
            "aarch64", "arm64",
            "mips64le", "mips64le",
            "ppc64le", "ppc64le",
            "s390x", "s390x",
    };

    class syzlang {
    public:
        std::string linux_kernel_version;
        std::string target;
        std::string work_dir;

        std::string file_prefix;
        std::map<llvm::StructType *, std::string> structure_name;

        std::string generate_dd(device_driver *dd, std::set<std::string> &resources);

        std::string
        generate_ioctl(sd::device_driver *dd, sd::cmd_info *cmd, llvm::Type *t, int64_t in_out, uint64_t index);

        // inout: 0 -- in, 1 -- out, 2 -- inout,
        std::string generate_type(llvm::Type *t, device_driver *dd = nullptr, int64_t inout = 0, bool opt = false);

        std::string generate_struct(llvm::StructType *st, device_driver *dd = nullptr);

        std::string generate_struct_name(llvm::StructType *st, device_driver *dd = nullptr);

        [[nodiscard]] std::string generate_general() const;

        void set_target(const std::string &t);

        std::string generate(device_driver *dd);

        std::string generate(llvm::Function *func, const std::vector<device_driver *> &dds);

        std::string generate_file_name(llvm::Function *func) const;

        bool is_opt_pointer(llvm::StructType *st, std::set<llvm::Type *> &checked, llvm::Type *t);

        std::string print_loc(llvm::Function *func, const std::vector<device_driver *> &dds);
    };
}


#endif //INC_2021_TEMPLATE_SYZLANG_H