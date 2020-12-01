<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input placeholder="请输入用户名（支持模糊搜索）" v-model="keyword" class="input-with-select" @keyup.enter.native="search">
          <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
        </el-input>
      </el-col>
      <el-col :span="2" :offset="1">
        <el-button type="primary" round @click="openForm({}, false)">添加用户</el-button>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
          v-loading="loading">
          <el-table-column
            fixed
            prop="id"
            label="学号"
            width="150">
          </el-table-column>
          <el-table-column
            prop="name"
            label="姓名"
            width="100">
          </el-table-column>
          <el-table-column
            prop="sex"
            label="性别"
            width="80">
          </el-table-column>
          <el-table-column
            prop="major"
            label="专业">
          </el-table-column>
          <el-table-column
            prop="uclass"
            label="班级">
          </el-table-column>
          <el-table-column
            prop="penalty"
            label="待缴罚款"
            width="100">
          </el-table-column>
          <el-table-column
            prop="borrowid"
            label="借书号"
            width="100">
          </el-table-column>
          <el-table-column
            prop="role"
            label="角色"
            width="100">
            <template slot-scope="scope">
              <el-tag
                :type="scope.row.role === 1 ? 'success' : 'primary'"
                disable-transitions>{{ scope.row.role === 1 ? '管理员' : '用户' }}
              </el-tag>
            </template>
          </el-table-column>
          <el-table-column
            fixed="right"
            label="操作"
            width="180">
            <template slot-scope="scope">
              <el-button @click="openForm(scope.row, true)" type="primary" size="small">编辑</el-button>
              <el-button type="danger" size="small" @click="deleteUser(scope.row.id)">删除</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="6" :offset="8">
        <el-pagination
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
    <user-form ref="userForm"/>
  </div>
</template>

<script>

import UserForm from "@/views/maintain/user/components/user_form";
import {deleteUser, getUserByUserName} from "@/api/user";

export default {
  name: 'Maintain-User',
  components: {UserForm},
  data() {
    return {
      loading: true,
      keyword: '',
      total: 0,
      currentPage: 1,
      pageSize: 5,
      form_visible: false,
      tableData: []
    }
  },
  created() {
    this.search()
  },
  computed: {},
  methods: {
    search() {
      this.loading = true
      getUserByUserName({name: this.keyword, page: this.currentPage - 1, size: this.pageSize}).then(response => {
        this.tableData = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
        this.loading = false
      })
    },
    deleteUser(id) {
      this.$confirm('此操作将删除该用户且无法撤销, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'error'
      }).then(() => {
        deleteUser({id: id}).then(response => {
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
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    openForm(row, edit) {
      this.$refs['userForm'].user = row;
      this.$refs['userForm'].visible = true;
      this.$refs['userForm'].edit = edit;
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
