<template>
  <el-dialog title="图书信息修改" :visible.sync="visible" width="40%">
    <el-form :inline="true" :model="book" :rules="rules" ref="book" label-width="100px" class="demo-ruleForm" :label-position="'left'">
      <el-form-item label="ISBN号" prop="isbn">
        <el-input v-model="book.isbn" :disabled="true"></el-input>
      </el-form-item>
      <el-form-item label="书名" prop="bookName" style="margin-left: 15px">
        <el-input v-model="book.bookName"></el-input>
      </el-form-item>
      <el-form-item label="类别" prop="type">
        <el-select v-model="book.type" placeholder="请选择图书的类别">
          <el-option label="编程" :value="1"></el-option>
          <el-option label="青春" :value="2"></el-option>
          <el-option label="历史" :value="3"></el-option>
        </el-select>
      </el-form-item>
      <el-form-item label="作者" prop="author">
        <el-input v-model="book.author"></el-input>
      </el-form-item>
      <el-form-item label="出版社" prop="publisher">
        <el-select
          v-model="book.publisher"
          filterable
          remote
          reserve-keyword
          placeholder="请选择出版社"
          :remote-method="queryPublisherList">
          <el-option
            v-for="item in publisherList"
            :key="item.id"
            :label="item.publisherName"
            :value="item.publisherName">
          </el-option>
        </el-select>
      </el-form-item>
      <el-form-item label="出版日期" prop="publishDate">
        <el-date-picker
          v-model="book.publishDate"
          value-format="yyyy-MM-dd"
          type="date"
          placeholder="选择日期">
        </el-date-picker>
      </el-form-item>
      <el-form-item label="馆藏本数" prop="num">
        <el-input-number v-model="book.num" :min="1" :max="100" label="图书本数"></el-input-number>
      </el-form-item>
      <el-form-item label="是否可借" prop="canBorrow" style="margin-left: 20px">
        <el-switch
          v-model="book.canBorrow"
          active-color="#13ce66"
          inactive-color="#ff4949"
          active-value="true"
          inactive-value="false"
          >
        </el-switch>
      </el-form-item>
    </el-form>
    <div slot="footer">
      <el-button type="primary" @click="updateBook" @keyup.enter.native="updateBook">提交更新</el-button>
      <el-button @click="resetForm('book')">重置</el-button>
    </div>
  </el-dialog>
</template>

<script>

import {getPublisherList} from "@/api/publisher";
import {updateBook} from "@/api/book";
import checkPermission from "@/utils/permission";

export default {
  name: "Book",
  data() {
    return {
      checkPermission,
      visible: false,
      publisherList: [],
      book: {
        isbn: '',
        bookName: '',
        type: '',
        author: '',
        publisher: '',
        publishDate: '',
        num: 0,
        canBorrow: false
      },
      rules: {
        name: [
          {required: true, message: '请输入活动名称', trigger: 'blur'},
          {min: 3, max: 5, message: '长度在 3 到 5 个字符', trigger: 'blur'}
        ]
      }
    };
  },
  watch: {
    'visible': function (value) {
      if (!value) {
        this.$refs['book'].resetFields()
        this.$parent.search()
      }
    }
  },
  created() {
    this.queryPublisherList('')
  },
  methods: {
    updateBook() {
      let self = this
      updateBook(this.book).then(response => {
        console.log(response)
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
    queryPublisherList(name) {
      getPublisherList({publisherName: name}).then(response => {
        this.publisherList = response.data
      })
    },
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          alert('submit!');
        } else {
          console.log('error submit!!');
          return false;
        }
      });
    },
    resetForm(formName) {
      this.$refs[formName].resetFields();
    }
  }
}
</script>

<style scoped>

</style>
