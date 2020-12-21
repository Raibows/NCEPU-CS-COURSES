<template>
  <el-dialog title="出版社信息" :visible.sync="visible" width="30%">
    <el-form :model="press" ref="press">
      <el-form-item label="名称" :label-width="formLabelWidth">
        <el-input v-model="press.publisherName" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="地址" :label-width="formLabelWidth">
        <el-input v-model="press.publisherAddr" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="电话" :label-width="formLabelWidth">
        <el-input v-model="press.phoneNumber" autocomplete="off"></el-input>
      </el-form-item>
    </el-form>
    <div slot="footer" class="dialog-footer">
      <el-button @click="visible = false">取 消</el-button>
      <el-button type="primary" @click="updatePress" v-if="edit">提交修改</el-button>
      <el-button type="primary" @click="addPublisher" v-else>创建</el-button>
    </div>
  </el-dialog>
</template>

<script>
import {addPublisher, updatePublisher} from "@/api/publisher";

export default {
  name: "Press-Form",
  data() {
    return {
      edit: false,
      visible: false,
      press: {
        id: '',
        phoneNumber: '',
        publisherAddr: '',
        publisherName: ''
      },
      formLabelWidth: '120px'
    };
  },
  watch: {
    'visible': function (value) {
      if (!value) {
        this.$refs['press'].resetFields()
        this.$parent.search()
      }
    }
  },
  methods: {
    updatePress() {
      let self = this
      updatePublisher(this.press).then(response => {
        self.$message({
          message: response.msg,
          type: 'success'
        });
        setTimeout(function () {
          self.visible = false
          self.$parent.search()
        }, 1000)
      })
    },
    addPublisher() {
      let self = this
      addPublisher(this.press).then(response => {
        self.$message({
          message: response.msg,
          type: 'success'
        });
        setTimeout(function () {
          self.visible = false
          self.$parent.search()
        }, 1000)
      })
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
