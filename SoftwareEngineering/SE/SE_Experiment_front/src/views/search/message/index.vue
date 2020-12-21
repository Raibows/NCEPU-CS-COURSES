<template>
  <el-row :gutter="20">

    <el-col :span="10" :offset="7">

      <el-card shadow="always" style="margin: 20px auto;background-color: #34bfa3">
        用户留言
      </el-card>

      <el-card
        v-for="(index, i) in commentList"
        :key="i"
        shadow="hover"
        :body-style="{ padding: '10px' }"
        style="margin: 10px 0"
      >
        <el-row>
          <el-col :span="1">
            <el-avatar src="https://cube.elemecdn.com/0/88/03b0d39583f48206768a7534e55bcpng.png"/>
          </el-col>
          <el-col :span="20" :offset="1">
            <p style="margin: 2px auto">{{ index.major + ' - ' + index.studentName }}</p>
            <p style="margin: 5px auto">{{ index.content }}</p>
            <time style="float: right; display: inline-block;">{{ index.publishDate }}</time>
          </el-col>
        </el-row>
      </el-card>
      <el-pagination
        :current-page="currentPage"
        :page-size="pageSize"
        :page-sizes="[5, 10, 30, 50]"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total"
        @size-change="handleSizeChange"
        @current-change="handleCurrentChange"
      />
    </el-col>
    <el-col :span="6">
      <el-form ref="form" :model="form" :rules="rules" label-width="80px" style="margin: 20px auto"
               @submit.native.prevent>
        <el-form-item label="留言内容" prop="content">
          <el-input v-model="form.content" type="textarea" :autosize="{ minRows: 4, maxRows: 8}"/>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="addComment">提交</el-button>
          <el-button>取消</el-button>
        </el-form-item>
      </el-form>
    </el-col>
  </el-row>
</template>

<script>
import {addComment, queryAllComment} from '@/api/comment'

export default {
  name: 'SearchMessage',
  data() {
    return {
      currentPage: 1,
      total: 0,
      pageSize: 10,
      commentList: [],
      form: {
        content: ''
      },
      rules: {
        content: [
          {required: true, message: '请输入留言内容', trigger: 'blur'}
        ]
      }
    }
  },
  created() {
    this.search()
  },
  methods: {
    search() {
      queryAllComment({page: this.currentPage - 1, size: this.pageSize}).then(response => {
        this.commentList = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
      })
    },
    addComment() {
      const self = this
      this.$refs['form'].validate((valid) => {
        if(valid){
          addComment({
            content: self.form.content,
            studentName: self.$store.getters.name,
            major: '软件1702',
            pass: true
          }).then(response => {
            self.$message({
              message: response.msg,
              type: 'success'
            })
            self.search()
          })
        }
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    onSubmit() {
      console.log('submit!')
    }
  }
}
</script>

<style scoped>
.line {
  text-align: center;
}
</style>

