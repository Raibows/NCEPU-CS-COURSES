<template>
  <el-dialog title="采访清单" :visible.sync="visible" width="40%">
    <el-form ref="book" :model="book" :rules="rules" label-width="80px" :label-position="'left'">
      <el-form-item label="ISBN号" prop="isbn">
        <el-input v-model="book.isbn"></el-input>
      </el-form-item>
      <el-form-item label="图书名称" prop="bookName">
        <el-input v-model="book.bookName"></el-input>
      </el-form-item>
      <el-form-item label="出版社" prop="bookSeller">
        <el-input v-model="book.bookSeller"></el-input>
      </el-form-item>
      <el-form-item label="价格" prop="price">
        <el-input-number v-model="book.price" :step="0.1" :min="0.1" :max="1000"></el-input-number>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="submit">确认提交</el-button>
        <el-button @click="resetForm">重置</el-button>
      </el-form-item>
    </el-form>
  </el-dialog>
</template>

<script>
import {addOrder} from "@/api/interview";

export default {
  name: "Interview-Interview",
  data() {
    return {
      visible: false,
      book: {
        isbn: '',
        bookName: '',
        bookSeller: '',
        price: '',
        num: 10,
        id: '',
        userId: ''
      },
      rules: {
        isbn: [
          {required: true, message: '请输入13位isbn号', trigger: 'blur'},
          {min: 13, max: 13, message: '请输入13位isbn号', trigger: 'blur'}
        ],
        bookName: [
          {required: true, message: '请输入书名', trigger: 'blur'}
        ],
        bookSeller: [
          {required: true, message: '请输入出版社', trigger: 'blur'}
        ],
        price: [
          {required: true, message: '请输入价格', trigger: 'blur'}
        ]
      },
    }
  },
  created() {

  },
  methods: {
    submit() {
      this.book.userId = this.$store.getters.userId
      this.book.id = Math.random().toString(36).slice(-8)
      let self = this
      addOrder(this.book).then(response => {
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
    resetForm() {
      this.$refs['book'].resetFields()
    }
  }
}
</script>

<style scoped>

</style>
