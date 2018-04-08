 * Copyright (c) 2000-2017 Apple Inc. All rights reserved.
#if !CONFIG_EMBEDDED
#endif
#include <vfs/vfs_disk_conditioner.h>
#include <libkern/section_keywords.h>

extern int paniclog_append_noflush(const char *format, ...);

#if !CONFIG_EMBEDDED
		paniclog_append_noflush("mp = %p, phys = %p, prev (%p: %p-%p)\n",
		paniclog_append_noflush("mp = %p, phys = %p, prev (!)\n", hook->mp, phys);
		paniclog_append_noflush("vp = %p, phys = %p, prev (%p: %p-%p)\n",
		paniclog_append_noflush("vp = %p, phys = %p, prev (!)\n", hook->vp, phys);
#endif //CONFIG_EMBEDDED
	/*
	 * The mount iterate mutex is held for the duration of the iteration.
	 * This can be done by a state flag on the mount structure but we can
	 * run into priority inversion issues sometimes.
	 * Using a mutex allows us to benefit from the priority donation
	 * mechanisms in the kernel for locks. This mutex should never be
	 * acquired in spin mode and it should be acquired before attempting to
	 * acquire the mount lock.
	 */
	mount_iterate_lock(mp);

	/* If it returns 0 then there is nothing to do */
		mount_iterate_unlock(mp);
#if !CONFIG_EMBEDDED
#endif
#if !CONFIG_EMBEDDED
#endif
#if !CONFIG_EMBEDDED
#endif
	mount_iterate_unlock(mp);
void
mount_iterate_lock(mount_t mp)
{
	lck_mtx_lock(&mp->mnt_iter_lock);
}

void
mount_iterate_unlock(mount_t mp)
{
	lck_mtx_unlock(&mp->mnt_iter_lock);
}

#if !CONFIG_EMBEDDED
			if (MNTK_VIRTUALDEV & mp->mnt_kern_flag)    speed = 128;
			else if (disk_conditioner_mount_is_ssd(mp)) speed = 7*256;
			else                                        speed = 256;
#endif
	/*
	 * See comments in vnode_iterate() for the rationale for this lock
	 */
	mount_iterate_lock(mp);

			mount_iterate_unlock(mp);
	/* If it returns 0 then there is nothing to do */
		mount_iterate_unlock(mp);
	mount_iterate_unlock(mp);
/*
 * vn_getpath_fsenter_with_parent will reenter the file system to fine the path of the
 * vnode.  It requires that there are IO counts on both the vnode and the directory vnode.
 *
 * vn_getpath_fsenter is called by MAC hooks to authorize operations for every thing, but
 * unlink, rmdir and rename. For these operation the MAC hook  calls vn_getpath. This presents
 * problems where if the path can not be found from the name cache, those operations can
 * erroneously fail with EPERM even though the call should succeed. When removing or moving
 * file system objects with operations such as unlink or rename, those operations need to
 * take IO counts on the target and containing directory. Calling vn_getpath_fsenter from a
 * MAC hook from these operations during forced unmount operations can lead to dead
 * lock. This happens when the operation starts, IO counts are taken on the containing
 * directories and targets. Before the MAC hook is called a forced unmount from another
 * thread takes place and blocks on the on going operation's directory vnode in vdrain.
 * After which, the MAC hook gets called and calls vn_getpath_fsenter.  vn_getpath_fsenter
 * is called with the understanding that there is an IO count on the target. If in
 * build_path the directory vnode is no longer in the cache, then the parent object id via
 * vnode_getattr from the target is obtain and used to call VFS_VGET to get the parent
 * vnode. The file system's VFS_VGET then looks up by inode in its hash and tries to get
 * an IO count. But VFS_VGET "sees" the directory vnode is in vdrain and can block
 * depending on which version and how it calls the vnode_get family of interfaces.
 *
 * N.B.  A reasonable interface to use is vnode_getwithvid. This interface was modified to
 * call vnode_getiocount with VNODE_DRAINO, so it will happily get an IO count and not
 * cause issues, but there is no guarantee that all or any file systems are doing that.
 *
 * vn_getpath_fsenter_with_parent can enter the file system safely since there is a known
 * IO count on the directory vnode by calling build_path_with_parent.
 */

int
vn_getpath_fsenter_with_parent(struct vnode *dvp, struct vnode *vp, char *pathbuf, int *len)
{
	return build_path_with_parent(vp, dvp, pathbuf, *len, len, 0, vfs_context_current());
}

	} else {
		/* Check for APFS Fusion */
		dk_apfs_flavour_t flavour;
		if ((VNOP_IOCTL(devvp, DKIOCGETAPFSFLAVOUR, (caddr_t)&flavour, 0, ctx) == 0) &&
		    (flavour == DK_APFS_FUSION)) {
			mp->mnt_ioflags |= MNT_IOFLAGS_FUSION_DRIVE;
		}
	MALLOC(fsidlst, fsid_t *, req->oldlen, M_TEMP, M_WAITOK | M_ZERO);
				strlcpy(&sfs.f_fstypename[0], &mp->fstypename_override[0], MFSNAMELEN);
#ifdef NFSCLIENT
				strlcpy(&sfs.f_fstypename[0], &mp->fstypename_override[0], MFSNAMELEN);
static int	filt_fsattach(struct knote *kn, struct kevent_internal_s *kev);
SECURITY_READ_ONLY_EARLY(struct filterops) fs_filtops = {
	.f_attach = filt_fsattach,
	.f_detach = filt_fsdetach,
	.f_event = filt_fsevent,
filt_fsattach(struct knote *kn, __unused struct kevent_internal_s *kev)
	struct vfsconf vfsc = {};
/* Indicate that the root file system unmounted cleanly */
static int vfs_root_unmounted_cleanly = 0;
SYSCTL_INT(_vfs_generic, OID_AUTO, root_unmounted_cleanly, CTLFLAG_RD, &vfs_root_unmounted_cleanly, 0, "Root filesystem was unmounted cleanly");

void
vfs_set_root_unmounted_cleanly(void)
{
	vfs_root_unmounted_cleanly = 1;
}

static int vnode_authorize_callback_int(kauth_action_t action, vfs_context_t ctx,
    vnode_t vp, vnode_t dvp, int *errorp);
#define _VAC_NO_VNODE_POINTERS	(1<<4)
/*
 * Authorizer for directory cloning. This does not use vnodes but instead
 * uses prefilled vnode attributes from the filesystem.
 *
 * The same function is called to set up the attributes required, perform the
 * authorization and cleanup (if required)
 */
int
vnode_attr_authorize_dir_clone(struct vnode_attr *vap, kauth_action_t action,
    struct vnode_attr *dvap, __unused vnode_t sdvp, mount_t mp,
    dir_clone_authorizer_op_t vattr_op, uint32_t flags, vfs_context_t ctx,
    __unused void *reserved)
{
	int error;
	int is_suser = vfs_context_issuser(ctx);

	if (vattr_op == OP_VATTR_SETUP) {
		VATTR_INIT(vap);

		/*
		 * When ACL inheritence is implemented, both vap->va_acl and
		 * dvap->va_acl will be required (even as superuser).
		 */
		VATTR_WANTED(vap, va_type);
		VATTR_WANTED(vap, va_mode);
		VATTR_WANTED(vap, va_flags);
		VATTR_WANTED(vap, va_uid);
		VATTR_WANTED(vap, va_gid);
		if (dvap) {
			VATTR_INIT(dvap);
			VATTR_WANTED(dvap, va_flags);
		}

		if (!is_suser) {
			/*
			 * If not superuser, we have to evaluate ACLs and
			 * need the target directory gid to set the initial
			 * gid of the new object.
			 */
			VATTR_WANTED(vap, va_acl);
			if (dvap)
				VATTR_WANTED(dvap, va_gid);
		} else if (dvap && (flags & VNODE_CLONEFILE_NOOWNERCOPY)) {
			VATTR_WANTED(dvap, va_gid);
		}
		return (0);
	} else if (vattr_op == OP_VATTR_CLEANUP) {
		return (0); /* Nothing to do for now */
	}

	/* dvap isn't used for authorization */
	error = vnode_attr_authorize(vap, NULL, mp, action, ctx);

	if (error)
		return (error);

	/*
	 * vn_attribute_prepare should be able to accept attributes as well as
	 * vnodes but for now we do this inline.
	 */
	if (!is_suser || (flags & VNODE_CLONEFILE_NOOWNERCOPY)) {
		/*
		 * If the filesystem is mounted IGNORE_OWNERSHIP and an explicit
		 * owner is set, that owner takes ownership of all new files.
		 */
		if ((mp->mnt_flag & MNT_IGNORE_OWNERSHIP) &&
		    (mp->mnt_fsowner != KAUTH_UID_NONE)) {
			VATTR_SET(vap, va_uid, mp->mnt_fsowner);
		} else {
			/* default owner is current user */
			VATTR_SET(vap, va_uid,
			    kauth_cred_getuid(vfs_context_ucred(ctx)));
		}

		if ((mp->mnt_flag & MNT_IGNORE_OWNERSHIP) &&
		    (mp->mnt_fsgroup != KAUTH_GID_NONE)) {
			VATTR_SET(vap, va_gid, mp->mnt_fsgroup);
		} else {
			/*
			 * default group comes from parent object,
			 * fallback to current user
			 */
			if (VATTR_IS_SUPPORTED(dvap, va_gid)) {
				VATTR_SET(vap, va_gid, dvap->va_gid);
			} else {
				VATTR_SET(vap, va_gid,
				    kauth_cred_getgid(vfs_context_ucred(ctx)));
			}
		}
	}

	/* Inherit SF_RESTRICTED bit from destination directory only */
	if (VATTR_IS_ACTIVE(vap, va_flags)) {
		VATTR_SET(vap, va_flags,
		    ((vap->va_flags & ~(UF_DATAVAULT | SF_RESTRICTED)))); /* Turn off from source */
		 if (VATTR_IS_ACTIVE(dvap, va_flags))
			VATTR_SET(vap, va_flags,
			    vap->va_flags | (dvap->va_flags & (UF_DATAVAULT | SF_RESTRICTED)));
	} else if (VATTR_IS_ACTIVE(dvap, va_flags)) {
		VATTR_SET(vap, va_flags, (dvap->va_flags & (UF_DATAVAULT | SF_RESTRICTED)));
	}

	return (0);
}


vnode_authorize_checkimmutable(mount_t mp, struct vnode_attr *vap, int rights, int ignore)
	switch(vap->va_type) {
		if (vap->va_type == VDIR) {
vnode_authorize_callback(__unused kauth_cred_t cred, __unused void *idata,
    kauth_action_t action, uintptr_t arg0, uintptr_t arg1, uintptr_t arg2,
    uintptr_t arg3)
        result = vnode_authorize_callback_int(action, ctx, vp, dvp, (int *)arg3);
static int
vnode_attr_authorize_internal(vauth_ctx vcp, mount_t mp,
    kauth_ace_rights_t rights, int is_suser, boolean_t *found_deny,
    int noimmutable, int parent_authorized_for_delete_child)
{
	int result;

	/*
	 * Check for immutability.
	 *
	 * In the deletion case, parent directory immutability vetoes specific
	 * file rights.
	 */
	if ((result = vnode_authorize_checkimmutable(mp, vcp->vap, rights,
	    noimmutable)) != 0)
		goto out;

	if ((rights & KAUTH_VNODE_DELETE) &&
	    !parent_authorized_for_delete_child) {
		result = vnode_authorize_checkimmutable(mp, vcp->dvap,
		    KAUTH_VNODE_DELETE_CHILD, 0);
		if (result)
			goto out;
	}

	/*
	 * Clear rights that have been authorized by reaching this point, bail if nothing left to
	 * check.
	 */
	rights &= ~(KAUTH_VNODE_LINKTARGET | KAUTH_VNODE_CHECKIMMUTABLE);
	if (rights == 0)
		goto out;

	/*
	 * If we're not the superuser, authorize based on file properties;
	 * note that even if parent_authorized_for_delete_child is TRUE, we
	 * need to check on the node itself.
	 */
	if (!is_suser) {
		/* process delete rights */
		if ((rights & KAUTH_VNODE_DELETE) &&
		    ((result = vnode_authorize_delete(vcp, parent_authorized_for_delete_child)) != 0))
		    goto out;

		/* process remaining rights */
		if ((rights & ~KAUTH_VNODE_DELETE) &&
		    (result = vnode_authorize_simple(vcp, rights, rights & KAUTH_VNODE_DELETE, found_deny)) != 0)
			goto out;
	} else {
		/*
		 * Execute is only granted to root if one of the x bits is set.  This check only
		 * makes sense if the posix mode bits are actually supported.
		 */
		if ((rights & KAUTH_VNODE_EXECUTE) &&
		    (vcp->vap->va_type == VREG) &&
		    VATTR_IS_SUPPORTED(vcp->vap, va_mode) &&
		    !(vcp->vap->va_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
			result = EPERM;
			KAUTH_DEBUG("%p    DENIED - root execute requires at least one x bit in 0x%x", vp, va.va_mode);
			goto out;
		}

		/* Assume that there were DENYs so we don't wrongly cache KAUTH_VNODE_SEARCHBYANYONE */
		*found_deny = TRUE;

		KAUTH_DEBUG("%p    ALLOWED - caller is superuser", vp);
	}
out:
	return (result);
}
vnode_authorize_callback_int(kauth_action_t action, vfs_context_t ctx,
    vnode_t vp, vnode_t dvp, int *errorp)
	vcp->ctx = ctx;
	vcp->vp = vp;
	vcp->dvp = dvp;
		vcp->dvp = NULLVP;
		vcp->dvap = NULL;
	VATTR_WANTED(&va, va_type);
	VATTR_RETURN(&va, va_type, vnode_vtype(vp));

	if (vcp->dvp) {
		if ((result = vnode_getattr(vcp->dvp, &dva, ctx)) != 0) {
		VATTR_WANTED(&dva, va_type);
		VATTR_RETURN(&dva, va_type, vnode_vtype(vcp->dvp));
	result = vnode_attr_authorize_internal(vcp, vp->v_mount, rights, is_suser,
	    &found_deny, noimmutable, parent_authorized_for_delete_child);
int
vnode_attr_authorize_init(struct vnode_attr *vap, struct vnode_attr *dvap,
    kauth_action_t action, vfs_context_t ctx)
{
	VATTR_INIT(vap);
	VATTR_WANTED(vap, va_type);
	VATTR_WANTED(vap, va_mode);
	VATTR_WANTED(vap, va_flags);
	if (dvap) {
		VATTR_INIT(dvap);
		if (action & KAUTH_VNODE_DELETE) {
			VATTR_WANTED(dvap, va_type);
			VATTR_WANTED(dvap, va_mode);
			VATTR_WANTED(dvap, va_flags);
		}
	} else if (action & KAUTH_VNODE_DELETE) {
		return (EINVAL);
	}

	if (!vfs_context_issuser(ctx)) {
		VATTR_WANTED(vap, va_uid);
		VATTR_WANTED(vap, va_gid);
		VATTR_WANTED(vap, va_acl);
		if (dvap && (action & KAUTH_VNODE_DELETE)) {
			VATTR_WANTED(dvap, va_uid);
			VATTR_WANTED(dvap, va_gid);
			VATTR_WANTED(dvap, va_acl);
		}
	}

	return (0);
}

int
vnode_attr_authorize(struct vnode_attr *vap, struct vnode_attr *dvap, mount_t mp,
    kauth_action_t action, vfs_context_t ctx)
{
	struct _vnode_authorize_context auth_context;
	vauth_ctx vcp;
	kauth_ace_rights_t rights;
	int noimmutable;
	boolean_t found_deny;
	boolean_t is_suser = FALSE;
	int result = 0;

	vcp = &auth_context;
	vcp->ctx = ctx;
	vcp->vp = NULLVP;
	vcp->vap = vap;
	vcp->dvp = NULLVP;
	vcp->dvap = dvap;
	vcp->flags = vcp->flags_valid = 0;

	noimmutable = (action & KAUTH_VNODE_NOIMMUTABLE) ? 1 : 0;
	rights = action & ~(KAUTH_VNODE_ACCESS | KAUTH_VNODE_NOIMMUTABLE);

	/*
	 * Check for read-only filesystems.
	 */
	if ((rights & KAUTH_VNODE_WRITE_RIGHTS) &&
	    mp && (mp->mnt_flag & MNT_RDONLY) &&
	    ((vap->va_type == VREG) || (vap->va_type == VDIR) ||
	    (vap->va_type == VLNK) || (rights & KAUTH_VNODE_DELETE) ||
	    (rights & KAUTH_VNODE_DELETE_CHILD))) {
		result = EROFS;
		goto out;
	}

	/*
	 * Check for noexec filesystems.
	 */
	if ((rights & KAUTH_VNODE_EXECUTE) &&
	    (vap->va_type == VREG) && mp && (mp->mnt_flag & MNT_NOEXEC)) {
		result = EACCES;
		goto out;
	}

	if (vfs_context_issuser(ctx)) {
		/*
		 * if we're not asking for execute permissions or modifications,
		 * then we're done, this action is authorized.
		 */
		if (!(rights & (KAUTH_VNODE_EXECUTE | KAUTH_VNODE_WRITE_RIGHTS)))
			goto out;
		is_suser = TRUE;
	} else {
		if (!VATTR_IS_SUPPORTED(vap, va_uid) ||
		    !VATTR_IS_SUPPORTED(vap, va_gid) ||
		    (mp && vfs_extendedsecurity(mp) && !VATTR_IS_SUPPORTED(vap, va_acl))) {
			panic("vnode attrs not complete for vnode_attr_authorize\n");
		}
	}

	result = vnode_attr_authorize_internal(vcp, mp, rights, is_suser,
	    &found_deny, noimmutable, FALSE);

	if (result == EPERM)
		result = EACCES;
out:
	return (result);
}


	int		has_priv_suser, ismember, defaulted_owner, defaulted_group, defaulted_mode;
	uint32_t	inherit_flags;
	inherit_flags = 0;
	if (VATTR_IS_SUPPORTED(&dva, va_flags)) {
		inherit_flags = dva.va_flags & (UF_DATAVAULT | SF_RESTRICTED);
	if (inherit_flags) {
		VATTR_SET(vap, va_flags, (vap->va_flags | inherit_flags));
	    VATTR_IS_ACTIVE(vap, va_backup_time) ||
	    VATTR_IS_ACTIVE(vap, va_addedtime)) {
	    VATTR_IS_ACTIVE(vap, va_backup_time) ||
	    VATTR_IS_ACTIVE(vap, va_addedtime)) {
	paniclog_append_noflush("\n***** VNODES *****\n"
			paniclog_append_noflush("Unable to iterate the mount list %p - encountered an invalid mount pointer %p \n",
				paniclog_append_noflush("Unable to iterate the vnode list %p - encountered an invalid vnode pointer %p \n",
			paniclog_append_noflush("%s %0d %0d %s\n",
#if CONFIG_MACF
	int rv = mac_vnode_check_trigger_resolve(ctx, vp, &ndp->ni_cnd);
	if (rv != 0)
		return rv;
#endif
