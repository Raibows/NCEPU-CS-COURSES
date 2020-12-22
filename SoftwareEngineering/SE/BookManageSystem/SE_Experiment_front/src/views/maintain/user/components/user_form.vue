<template>
  <el-dialog title="用户信息" :visible.sync="visible" width="40%">
    <el-form :model="user" :rules="rules" ref="user" :label-position="'left'" :inline="true">
      <el-form-item label="学号" prop="id" :label-width="formLabelWidth">
        <el-input v-model="user.id" autocomplete="off" :disabled="edit"></el-input>
      </el-form-item>
      <el-form-item label="姓名" prop="name" :label-width="formLabelWidth">
        <el-input v-model="user.name" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="性别" prop="sex" :label-width="formLabelWidth">
        <el-radio v-model="user.sex" label="男">男</el-radio>
        <el-radio v-model="user.sex" label="女">女</el-radio>
      </el-form-item>
      <el-form-item label="角色" prop="role" :label-width="formLabelWidth" style="margin-left: 80px">
        <el-radio v-model="user.role" :label="0" :disabled="edit">用户</el-radio>
        <el-radio v-model="user.role" :label="1" :disabled="edit">管理员</el-radio>
      </el-form-item>
      <el-form-item label="专业" prop="major" :label-width="formLabelWidth">
        <el-input v-model="user.major" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="班级" prop="uclass" :label-width="formLabelWidth">
        <el-input v-model="user.uclass" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="借书号" prop="borrowid" :label-width="formLabelWidth">
        <el-input v-model="user.borrowid" autocomplete="off" :disabled="edit"></el-input>
      </el-form-item>
      <el-form-item label="借书本数" prop="borrowNum" :label-width="formLabelWidth">
        <el-input-number v-model="user.borrowNum" :step="1"></el-input-number>
      </el-form-item>
      <el-form-item label="密码" prop="pwd" :label-width="formLabelWidth">
        <el-input v-model="user.pwd" autocomplete="off"></el-input>
      </el-form-item>
    </el-form>
    <div slot="footer" class="dialog-footer">
      <el-button @click="visible = false">取 消</el-button>
      <el-button type="primary" @click="updateUser" v-if="edit">更新用户</el-button>
      <el-button type="primary" @click="addUser" v-else>添加用户</el-button>
    </div>
  </el-dialog>
</template>

<script>
import {addUser, updateUser} from "@/api/user";

export default {
  name: "User-Form",
  data() {
    return {
      visible: false,
      edit: false,
      user: {
        id: '',
        name: '',
        sex: '',
        pwd: '',
        role: '',
        major: '',
        uclass: '',
        borrowid: '',
        borrowNum: 0

      },
      rules: {
        id: [
          {required: true, message: '请输入12位学号', trigger: 'blur'},
          {min: 12, max: 12, message: '请输入12位学号', trigger: 'blur'}
        ],
        name: [
          {required: true, message: '请输入姓名', trigger: 'blur'}
        ],
        sex: [
          {required: true, message: '请选择性别', trigger: 'blur'}
        ],
        role: [
          {required: true, message: '请选择角色', trigger: 'blur'}
        ],
        major: [
          {required: true, message: '请输入专业', trigger: 'blur'}
        ],
        uclass: [
          {required: true, message: '请输入班级', trigger: 'blur'}
        ],
        borrowid: [
          {required: true, message: '请输入借书号', trigger: 'blur'}
        ],
        borrowNum: [
          {required: true, message: '请输入借书本数', trigger: 'blur'}
        ],
        pwd: [
          {required: true, message: '请输入密码', trigger: 'blur'}
        ]
      },
      formLabelWidth: '80px'
    };
  },
  watch: {
    'visible': function (value) {
      if (!value) {
        this.$refs['user'].resetFields()
        this.$parent.search()
      }
    }
  },
  methods: {
    updateUser() {
      let self = this
      self.$refs['user'].validate((valid) => {
        if (valid) {
          updateUser(self.user).then(response => {
            self.$message({
              message: response.msg,
              type: 'success'
            });
            setTimeout(function () {
              self.visible = false
              self.$parent.search()
            }, 1000)
          })
        } else {
        }
      });
    },
    addUser() {
      let self = this
      self.$refs['user'].validate((valid) => {
        if (valid) {
          addUser(self.user).then(response => {
            self.$message({
              message: response.msg,
              type: 'success'
            });
            setTimeout(function () {
              self.visible = false
              self.$parent.search()
            }, 1000)
          })
        } else {
        }
      });
    }
  }
  // props: {
  //   visible : {
  //     type: Boolean,
  //     required: true
  //   }
  // }
}
</script>

<style scoped>

</style>
