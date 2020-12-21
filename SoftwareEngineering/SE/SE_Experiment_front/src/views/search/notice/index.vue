<template>
  <el-row :gutter="20">
    <el-col :span="10" style="margin: 20px" v-if="checkPermission(['admin'])">
      <el-form ref="form" :model="notice" :rules="rules" label-width="100px" :label-position="'left'">
        <el-form-item label="发布人" prop="publisher">
          <el-input v-model="notice.publisher"></el-input>
        </el-form-item>
        <el-form-item label="通知标题" prop="title">
          <el-input v-model="notice.title"></el-input>
        </el-form-item>
        <el-form-item label="通知类型" prop="type">
          <el-select v-model="notice.type" placeholder="请选择通知类型">
            <el-option label="公告" :value="1"></el-option>
            <el-option label="提醒" :value="0"></el-option>
          </el-select>
        </el-form-item>
        <el-form-item label="通知时间段" prop="date_range">
          <el-date-picker
            v-model="notice.date_range"
            type="daterange"
            value-format="yyyy-MM-dd"
            range-separator="至"
            start-placeholder="开始日期"
            end-placeholder="结束日期">
          </el-date-picker>
        </el-form-item>
        <el-form-item label="通知正文" prop="content">
          <el-input type="textarea" v-model="notice.content"></el-input>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="addAnn">立即创建</el-button>
          <el-button>取消</el-button>
        </el-form-item>
      </el-form>
    </el-col>
    <el-col :span="12" style="margin: 20px">
      <!--      <el-input placeholder="请输入内容" v-model="keyword" class="input-with-select" @keyup.enter.native="search">-->
      <!--        <el-button slot="append" icon="el-icon-search" @click="search"></el-button>-->
      <!--      </el-input>-->
      <el-table
        :data="tableData"
        style="width: 100%;margin-top: 20px ">
        <el-table-column
          label="发布时间"
          width="100"
          prop="publishDate">
        </el-table-column>
        <el-table-column
          label="截止时间"
          width="100"
          prop="endDate">
        </el-table-column>
        <el-table-column
          label="发布者"
          prop="publisher">
        </el-table-column>
        <el-table-column
          label="标题"
          prop="title">
        </el-table-column>
        <el-table-column
          label="正文"
          prop="content">
        </el-table-column>
        <el-table-column width="160" label="操作" v-if="checkPermission(['admin'])">
          <template slot-scope="scope">
            <el-button
              fixed="right"
              size="mini"
              type="success"
              @click="insert(scope.row)">填入
            </el-button>
            <el-button
              size="mini"
              type="danger"
              @click="deleteAnn(scope.row.id)">删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>
      <el-pagination
        style="margin-top: 20px;margin-left: 25%"
        @size-change="handleSizeChange"
        @current-change="handleCurrentChange"
        :current-page="currentPage"
        :page-sizes="[5, 10, 30, 50]"
        :page-size="pageSize"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-col>
  </el-row>
</template>

<script>

import checkPermission from '@/utils/permission'
import {addAnn, deleteAnn, queryAllAnn} from "@/api/announcement";
import {deleteUser} from "@/api/user"; // 权限判断函数

export default {
  name: 'Search-Notice',
  data() {
    return {
      keyword: '',
      total: 0,
      currentPage: 1,
      pageSize: 5,
      notice: {
        publisher: '',
        title: '',
        type: '',
        date_range: [],
        content: '',
        endDate: '',
        publishDate: ''
      },
      rules: {
        publisher: [
          {required: true, message: '请输入发布者姓名', trigger: 'blur'}
        ],
        title: [
          {required: true, message: '请输入通知标题', trigger: 'blur'}
        ],
        type: [
          {required: true, message: '请选择通知类型', trigger: 'blur'}
        ],
        date_range: [
          {required: true, message: '请选择通知时间', trigger: 'blur'}
        ],
        content: [
          {required: true, message: '请输入通知正文', trigger: 'blur'}
        ]
      },
      tableData: []
    }
  },
  created() {
    this.search()
  },
  methods: {
    checkPermission,
    search() {
      queryAllAnn({name: this.keyword, page: this.currentPage - 1, size: this.pageSize}).then(response => {
        this.tableData = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
      })
    },
    insert(row) {
      this.notice.title = row.title
      this.notice.publisher = row.publisher
      this.notice.type = row.type
      this.notice.content = row.content
      this.notice.date_range = []
      this.notice.date_range.push(row.publishDate)
      this.notice.date_range.push(row.endDate)
    },
    addAnn() {
      this.$refs['form'].validate((valid) => {
        if (valid) {
          this.notice.publishDate = this.notice.date_range[0]
          this.notice.endDate = this.notice.date_range[1]
          addAnn(this.notice).then(response => {
            this.$message({
              type: 'success',
              message: response.msg
            });
            this.search()
          })
        }
      })
    },
    deleteAnn(id) {
      this.$confirm('此操作将删除该公告, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        deleteAnn({id: id}).then(response => {
          this.search()
          this.$message({
            type: 'success',
            message: response.msg
          });
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    }
    ,
    onSubmit() {
      console.log('submit!');
    }
    ,
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    }
    ,
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    }
  }
}
</script>

<style scoped>
.line {
  text-align: center;
}
</style>

